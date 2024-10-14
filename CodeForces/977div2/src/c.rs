use std::{collections::{BTreeSet, HashSet}, io::{self, prelude::*}};

fn add_to_ord(idx: usize, place: usize, ord: &mut BTreeSet<(usize, usize)>, nxt: &[isize], mut cnt: isize) -> isize {
    if let Some(prev) = ord.range(..(place, idx)).next_back() {
        let (prev_place, prev_idx) = *prev;
        if let Some(next) = ord.range((place + 1, 0)..).next() {
            let (nxt_place, nxt_idx) = *next;
            if nxt[prev_idx] == nxt_idx as isize {
                cnt -= 1;
            }
        }
    }

    ord.insert((place, idx));

    if let Some(next) = ord.range((place + 1, 0)..).next() {
        let (nxt_place, nxt_idx) = *next;
        if nxt[idx] == nxt_idx as isize {
            cnt += 1;
        }
    }

    if let Some(prev) = ord.range(..(place, 0)).next_back() {
        let (prev_place, prev_idx) = *prev;
        if nxt[prev_idx] == idx as isize {
            cnt += 1;
        }
    }

    cnt
}

fn remove_from_ord(idx: usize, place: usize, ord: &mut BTreeSet<(usize, usize)>, nxt: &[isize], mut cnt: isize) -> isize {
    if let Some(next) = ord.range((place + 1, 0)..).next() {
        let (nxt_place, nxt_idx) = *next;
        if nxt[idx] == nxt_idx as isize {
            cnt -= 1;
        }
    }
    if let Some(prev) = ord.range(..(place, 0)).next_back() {
        let (prev_place, prev_idx) = *prev;
        if nxt[prev_idx] == idx as isize {
            cnt -= 1;
        }
    }
    ord.remove(&(place, idx));
    if let Some(prev) = ord.range(..(place, idx)).next_back() {
        let (prev_place, prev_idx) = *prev;
        if let Some(next) = ord.range((place + 1, 0)..).next() {
            let (nxt_place, nxt_idx) = *next;
            if nxt[prev_idx] == nxt_idx as isize {
                cnt += 1;
            }
        }
    }
    cnt
}



fn main() {
    let mut input = Scanner::from(io::stdin().lock());
    let mut writer = io::BufWriter::new(io::stdout().lock());
    let tc = input.token::<u32>();
    for cn in 0..tc {
        let (n, m, q) = (input.token::<usize>(), input.token::<usize>(), input.token::<u32>());
        let mut a = (0..n).map(|_| input.token::<usize>()-1).collect::<Vec<_>>();
        let mut b = (0..m).map(|_| input.token::<usize>()-1).collect::<Vec<_>>();
        let mut occ: Vec<BTreeSet<usize>> = (0..n).map(|_| BTreeSet::new()).collect();
        let mut nxt = vec![-1isize; n];
        for i in 0..n {
            if i + 1 < n {
                nxt[a[i]] = a[i+1] as isize;
            }
        }
        for i in 0..m {
            occ[b[i]].insert(i);
        }
        let mut cnt = 0;
        let mut ord: BTreeSet<(usize, usize)> = BTreeSet::new();

        for i in 0..n {
            if occ[a[i]].len() > 0 {
                cnt = add_to_ord(a[i], *occ[a[i]].iter().next().unwrap(), &mut ord, &nxt, cnt);
            }
            // writeln!(writer, "at index {i} cnt = {cnt}");
        }
        let mut unique_count = ord.len() as isize;
        let mut first = ord.len() > 0 && ord.iter().next().unwrap().1 == a[0];
        writeln!(writer, "{}", if cnt == unique_count-1 && first {"YA"} else {"TIDAK"});
        for i in 0..q {
            let (mut x, mut y) = (input.token::<usize>(), input.token::<usize>());
            x -= 1;
            y -= 1;
            let old_y = b[x];
            cnt = remove_from_ord(old_y, *occ[old_y].iter().next().unwrap(), &mut ord, &nxt, cnt);
            occ[old_y].remove(&x);
            if occ[old_y].len() > 0 {
                cnt = add_to_ord(old_y, *occ[old_y].iter().next().unwrap(), &mut ord, &nxt, cnt);
            }
            b[x] = y;
            if occ[y].len() > 0 {
                cnt = remove_from_ord(y, *occ[y].iter().next().unwrap(), &mut ord, &nxt, cnt);
            }
            occ[y].insert(x);
            if occ[y].len() > 0 {
                cnt = add_to_ord(y, *occ[y].iter().next().unwrap(), &mut ord, &nxt, cnt);
            }
            unique_count = ord.len() as isize;
            first = ord.len() > 0 && ord.iter().next().unwrap().1 == a[0];
            writeln!(writer, "{}", if cnt == unique_count-1 && first {"YA"} else {"TIDAK"});
        }
    }
}

pub struct Scanner<B> {
    reader: B,
    buffer: Vec<String>,
}

impl<R: BufRead> Scanner<R> {
    pub fn token<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            self.reader.read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

impl<R: BufRead> From<R> for Scanner<R> {
    fn from(reader: R) -> Self {
        Self {
            reader,
            buffer: Vec::new(),
        }
    }
}
