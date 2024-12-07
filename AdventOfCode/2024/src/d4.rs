use std::{cmp::min, fs::File, io::{BufRead, BufReader}};

fn read_lines() -> Vec<String> {
    let file = File::open("./input/d4p1.in").unwrap();
    let reader = BufReader::new(file);
    reader.lines().map(|x| x.unwrap()).collect::<Vec<String>>()
}

fn part1(lines: &Vec<String>) {
    let r = lines.len();
    let c = lines[0].len();
    let target = "XMAS";
    let mut ans = 0;
    let dirs: Vec<(i32, i32)> = vec![(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)];
    for i in 0..r {
        for j in 0..c {
            for (dr, dc) in &dirs {
                if target.chars().enumerate().all(|(idx, ch)| {
                    let ni = i as i32 + (idx as i32) * *dr;
                    let nj = j as i32 + (idx as i32) * *dc;
                    min(ni, nj) >= 0 && (0..r).contains(&(ni as usize)) && (0..c).contains(&(nj as usize)) && lines[ni as usize][nj as usize..nj as usize +1] == ch.to_string()
                }) {
                    ans += 1;
                }
            }
        }
    }
    println!("{}", ans);
}

fn part2(lines: &Vec<String>) {
    let r = lines.len();
    let c = lines[0].len();
    let mut ans = 0;
    for i in 0..=r-3 {
        for j in 0..=c-3 {
            if lines[i+1][j+1..j+2] != 'A'.to_string() {
                continue;
            }
            let d1 = format!("{}{}", &lines[i][j..j+1], &lines[i+2][j+2..j+3]);
            let d2 = format!("{}{}", &lines[i][j+2..j+3], &lines[i+2][j..j+1]);
            if (d1 == "MS" || d1 == "SM") && (d2 == "MS" || d2 == "SM") {
                ans += 1;
            }
        }
    }
    println!("{}", ans);
}

pub fn main() {
    let lines = read_lines();
    part1(&lines);
    part2(&lines);
}
