use std::{collections::HashSet, fs::File, io::{BufRead, BufReader}};

pub fn main() {
    let input = File::open("input/d10.in").unwrap();
    let reader = BufReader::new(input);
    let grid = reader.lines().map(|l| l.unwrap().chars().map(|c| c as i32 - '0' as i32).collect::<Vec<_>>()).collect::<Vec<_>>();
    let (n, m) = (grid.len(), grid[0].len());
    let dirs = vec![(1, 0), (0, 1), (-1, 0), (0, -1)];
    let mut res = vec![vec![HashSet::new(); m]; n];
    let mut paths = vec![vec![0; m]; n];
    let mut ans = 0;
    let mut anspaths = 0;
    for p in (0..10).rev() {
        for i in 0..n {
            for j in 0..m {
                if grid[i][j] != p { continue; }
                if p == 9 { 
                    res[i][j].insert((i, j));
                    paths[i][j] = 1;
                    continue;
                }
                for (dr, dc) in &dirs {
                    let (i1, j1) = (i as i32 + dr, j as i32 + dc);
                    if !((0..n).contains(&(i1 as usize)) && (0..m).contains(&(j1 as usize))) || grid[i1 as usize][j1 as usize] != 1 + p {
                        continue;
                    }
                    let s = HashSet::<(usize, usize)>::from_iter(res[i1 as usize][j1 as usize].iter().cloned());
                    res[i][j].extend(s);
                    paths[i][j] += paths[i1 as usize][j1 as usize];
                }
                if p == 0 { 
                    ans += res[i][j].len();
                    anspaths += paths[i][j];
                    // println!("{i},{j},{}", res[i][j].len());
                }
            }
        }
    }
    println!("{} {}", ans, anspaths);
}
