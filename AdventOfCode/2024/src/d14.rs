use std::{cmp::max, fs::File, io::{BufRead, BufReader, BufWriter, Write}};

use regex::Regex;

pub fn main() {
    let reader = BufReader::new(File::open("input/d14.in").unwrap());
    let mut writer = BufWriter::new(File::create("output/d14.out").unwrap());
    let regex = Regex::new(r"p=(\d*),(\d*) v=(-?\d*),(-?\d*)").unwrap();
    let mut cnt = vec![vec![0; 2]; 2];
    let mut bots = Vec::new();
    let (w, h) = (101, 103);
    reader.lines().for_each(|line| {
        regex.captures_iter(&line.unwrap()).map(|c| c.extract()).for_each(|(idx, [x, y, dx, dy])| {
            let (x, y, dx, dy) = (x.parse::<i32>().unwrap(), y.parse::<i32>().unwrap(), dx.parse::<i32>().unwrap(), dy.parse::<i32>().unwrap());
            // dbg!(x, y, dx, dy);
            bots.push((x, y, dx, dy));
            let x = x + dx * 100;
            let x = (x % w + w) % w;
            let y = y + dy * 100;
            let y = (y % h + h) % h;
            if x != w/2 && y != h/2 {
                cnt[if x < w/2 { 0 } else { 1 }][if y < h/2 { 0 } else { 1 }] += 1;
            }
        });
    });
    let ans = cnt[0][0] * cnt[0][1] * cnt[1][0] * cnt[1][1];
    println!("{} {}", ans, bots.len());
    let lim = 10000;
    let mut found = 0;
    for t in 0..lim {
        if t % (lim/10) == 0 {
            println!("{}/10", t / (lim/10));
        }
        let mut grid = vec![vec!['.'; w as usize]; h as usize];
        for (x, y, dx, dy) in &bots {
            let x = x + dx * t;
            let x = (x % w + w) % w;
            let y = y + dy * t;
            let y = (y % h + h) % h;
            grid[y as usize][x as usize] = '#';
        }
        let mut mx = Vec::new();
        for y in 0..h {
            let mut m = -1;
            for x in 0..w {
                if grid[y as usize][x as usize] == '#' { m = x; }
            }
            if m != -1 {
                mx.push(m);
            }
        }
        let mut cur_run = 1;
        let mut max_run = 0;
        for i in 1..mx.len() {
            if mx[i] >= mx[i-1] {
                cur_run += 1;
            } else { cur_run = 1; }
            max_run = max(max_run, cur_run);
        }
        if max_run < 8 { continue; }
        found += 1;
        writeln!(writer, "{t}").unwrap();
        grid.iter().for_each(|v| { writeln!(writer, "{}", v.iter().collect::<String>()); });
    }
    println!("{} found", found);
    writer.flush();
}
