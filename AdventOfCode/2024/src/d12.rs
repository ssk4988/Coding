use std::{collections::VecDeque, fs::File, io::{BufRead, BufReader}};

pub fn main() {
    let input = File::open("input/d12.in").unwrap();
    let reader = BufReader::new(input);
    let grid = reader.lines().map(|l| l.unwrap().chars().collect::<Vec<_>>()).collect::<Vec<_>>();
    let (n, m) = (grid.len(), grid[0].len());
    let mut comp = vec![vec![-1; m]; n];
    let mut ans = 0;
    let mut ans2 = 0;
    let mut q = VecDeque::new();
    let dirs = vec![(1, 0), (0, 1), (-1, 0), (0, -1)];
    let mut comps = 0;
    let check = |r: i32, c: i32, ex| {
        if r < 0 || r >= n as i32 || c < 0 || c >= m as i32 || grid[r as usize][c as usize] != ex {
            false
        } else { true }
    };
    for i in 0..n {
        for j in 0..m {
            if comp[i][j] != -1 { continue; }
            let mut area = 0;
            let mut perim = 0;
            let mut sides = 0;
            q.push_back((i, j));
            while let Some((r, c)) = q.pop_front() {
                if comp[r][c] != -1 { continue; }
                comp[r][c] = comps;
                area += 1;
                perim += 4;

                for (k, (dr, dc)) in dirs.iter().enumerate() {
                    let (r1, c1) = (r as i32 + dr, c as i32 + dc);
                    if !check(r1, c1, grid[r][c]) {
                        let (dr1, dc1) = dirs[(k+1)%4];
                        let (r2, c2) = (r as i32 + dr1, c as i32 + dc1);
                        let (r3, c3) = (r as i32 + dr1 + dr, c as i32 + dc1 + dc);
                        if !check(r2, c2, grid[r][c]) || check(r3, c3, grid[r][c]) {
                            sides += 1;
                        }
                        continue;
                    }
                    perim -= 1;
                    q.push_back((r1 as usize, c1 as usize));
                }
            }
            comps += 1;
            ans += area * perim;
            ans2 += area * sides;
            // println!("{} {} {} {}", area, perim, sides, grid[i][j]);
        }
    }
    println!("{} {}", ans, ans2);
}
