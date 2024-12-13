use std::{fs::File, io::{BufRead, BufReader}};
use num::Integer;

fn charidx(c: char) -> u32 {
    if c == '.' { return 63; }
    let ci = c as u32;
    if 'a' as u32 <= ci && ci <= 'z' as u32 {
        return ci - 'a' as u32;
    }
    if 'A' as u32 <= ci && ci <= 'Z' as u32 {
        return ci + 26 - 'A' as u32;
    }
    ci + 52 - '0' as u32
}



pub fn main() {
    let mut input = File::open("input/d8.in").unwrap();
    let mut reader = BufReader::new(input);
    let grid = reader.lines().map(|line| line.unwrap().chars().collect::<Vec<_>>()).collect::<Vec<_>>();
    let (n, m) = (grid.len(), grid[0].len());
    let mut idxs = vec![Vec::new(); 62];
    for i in 0..n {
        for j in 0..m {
            let t = charidx(grid[i][j]);
            if t != 63 {
                idxs[t as usize].push((i as i32, j as i32));
            }
        }
    }
    let mut ant = vec![vec![false; m]; n];
    let mut ant2 = vec![vec![false; m]; n];
    idxs.iter().for_each(|v| {
        for i in 0..v.len() {
            let (r1, c1) = v[i];
            for j in 0..i {
                let (r2, c2) = v[j];
                let (dr, dc) = (r2 - r1, c2 - c1);
                let rat = dr.gcd(&dc);
                {
                    let (r3, c3) = (r2 + dr, c2 + dc);
                    let (r4, c4) = (r1 - dr, c1 - dc);
                    if (0..n).contains(&(r3 as usize)) && (0..m).contains(&(c3 as usize)) {
                        ant[r3 as usize][c3 as usize] = true;
                    }
                    if (0..n).contains(&(r4 as usize)) && (0..m).contains(&(c4 as usize)) {
                        ant[r4 as usize][c4 as usize] = true;
                    }
                }
                let (dr, dc) = (dr / rat, dc / rat);
                let (mut r3, mut c3) = (r2, c2);
                let (mut r4, mut c4) = (r1, c1);
                while (0..n).contains(&(r3 as usize)) && (0..m).contains(&(c3 as usize)) {
                    ant2[r3 as usize][c3 as usize] = true;
                    r3 += dr;
                    c3 += dc;
                }
                while (0..n).contains(&(r4 as usize)) && (0..m).contains(&(c4 as usize)) {
                    ant2[r4 as usize][c4 as usize] = true;
                    r4 -= dr;
                    c4 -= dc;
                }
            }
        }
    });
    let ans = ant.iter().flatten().filter(|&&x| x).count();
    let ans2 = ant2.iter().flatten().filter(|&&x| x).count();
    println!("{} {}", ans, ans2);
}
