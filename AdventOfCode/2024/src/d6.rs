use std::{collections::HashSet, fs::File, io::{BufRead, BufReader}};

fn part1(grid: &Vec<String>) {
    let (mut sr, mut sc) = (-1, -1);
    let (n, m) = (grid.len(), grid[0].len());
    for i in 0..n {
        for j in 0..m {
            if grid[i][j..j+1] == *"^" {
                (sr, sc) = (i as i32, j as i32);
            }
        }
    }
    let mut dir = 0;
    let dirs = vec![(-1, 0), (0, 1), (1, 0), (0, -1)];
    let mut seen = vec![vec![vec![false; 4]; m]; n];
    let mut sseen = HashSet::new();
    while (0..n).contains(&(sr as usize)) && (0..m).contains(&(sc as usize)) {
        if seen[sr as usize][sc as usize][dir] { break; }
        // dbg!(sr, sc, dir);
        let (sr1, sc1) = (sr + dirs[dir].0, sc + dirs[dir].1);
        seen[sr as usize][sc as usize][dir] = true;
        sseen.insert((sr, sc));
        if !(0..n).contains(&(sr1 as usize)) || !(0..m).contains(&(sc1 as usize)) {
            break;
        }
        if grid[sr1 as usize][(sc1 as usize)..(sc1 as usize)+1] == *"#" {
            dir = (dir+1) % 4;
            continue;
        }
        (sr, sc) = (sr1, sc1);
    }
    println!("{}", sseen.len());
}

fn loops(grid: &Vec<String>) -> bool {
    let (mut sr, mut sc) = (-1, -1);
    let (n, m) = (grid.len(), grid[0].len());
    for i in 0..n {
        for j in 0..m {
            if grid[i][j..j+1] == *"^" {
                (sr, sc) = (i as i32, j as i32);
            }
        }
    }
    let mut dir = 0;
    let dirs = vec![(-1, 0), (0, 1), (1, 0), (0, -1)];
    let mut seen = vec![vec![vec![false; 4]; m]; n];
    while (0..n).contains(&(sr as usize)) && (0..m).contains(&(sc as usize)) {
        if seen[sr as usize][sc as usize][dir] { return true; }
        // dbg!(sr, sc, dir);
        let (sr1, sc1) = (sr + dirs[dir].0, sc + dirs[dir].1);
        seen[sr as usize][sc as usize][dir] = true;
        if !(0..n).contains(&(sr1 as usize)) || !(0..m).contains(&(sc1 as usize)) {
            break;
        }
        if grid[sr1 as usize][(sc1 as usize)..(sc1 as usize)+1] == *"#" {
            dir = (dir+1) % 4;
            continue;
        }
        (sr, sc) = (sr1, sc1);
    }
    return false;
}

fn part2(grid: &mut Vec<String>) {
    let mut ans = 0;
    println!("{}", grid.len());
    for i in 0..grid.len() {
        let mut chars: Vec<char> = grid[i].chars().collect();
        for j in 0..chars.len() {
            let prv = chars[j];
            chars[j] = '#';
            grid[i] = chars.iter().collect();
            if loops(grid) {
                ans += 1;
            }
            chars[j] = prv;
            grid[i] = chars.iter().collect();
        }
        println!("{}", i);
    }
    println!("{}", ans);
}

pub fn main() {
    let input = File::open("input/d6.in").unwrap();
    let reader = BufReader::new(input);
    let mut grid = reader.lines().map(|line| line.unwrap()).collect::<Vec<String>>();
    part1(&grid);
    part2(&mut grid);
}
