use std::{fs::File, io::{BufRead, BufReader}};

fn push(r: i32, c: i32, dr: i32, dc: i32, grid: &mut Vec<Vec<char>>) -> bool {
    if r < 0 || c < 0 || r >= grid.len() as i32 || c >= grid[0].len() as i32 {
        return false;
    }
    match grid[r as usize][c as usize] {
        '#' => false,
        '.' => true,
        _ => {
            if !push(r+dr, c+dc, dr, dc, grid) { return false; }
            grid[(r+dr) as usize][(c+dc) as usize] = grid[r as usize][c as usize];
            grid[r as usize][c as usize] = '.';
            true
        }
    }
}

fn can_push(r: i32, c: i32, dr: i32, dc: i32, grid: &mut Vec<Vec<char>>) -> bool {
    if r < 0 || c < 0 || r >= grid.len() as i32 || c >= grid[0].len() as i32 {
        return false;
    }
    match grid[r as usize][c as usize] {
        '#' => false,
        '.' | '@' => true,
        _ => {
            let res1 = can_push(r+dr, c+dc, dr, dc, grid);
            let res2 = can_push()
            if !push(r+dr, c+dc, dr, dc, grid) { return false; }
            grid[(r+dr) as usize][(c+dc) as usize] = grid[r as usize][c as usize];
            grid[r as usize][c as usize] = '.';
            true
        }
    }
}

pub fn main() {
    let reader = BufReader::new(File::open("input/d15.in").unwrap());
    let mut moves = Vec::new();
    let mut grid = Vec::new();
    let mut seen = false;
    reader.lines().for_each(|line| {
        let line = line.unwrap();
        if line.len() == 0 {
            seen = true;
            return;
        }
        if seen {
            moves.extend(line.chars());
        } else {
            grid.push(line.chars().collect::<Vec<_>>());
        }
    });
    let (mut br, mut bc) = (0, 0);
    let (n, m) = (grid.len(), grid[0].len());
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == '@' {
                br = i;
                bc = j;
            }
        }
    }
    for c in moves {
        let (dr, dc) = match c {
            'v' => (1, 0),
            '^' => (-1, 0),
            '<' => (0, -1), 
            '>' => (0, 1),
            _ => (-1, -1)
        };

        if push(br as i32, bc as i32, dr, dc, &mut grid) {
            br = (br as i32 + dr) as usize;
            bc = (bc as i32 + dc) as usize;
        }
    }
    let mut ans = 0;
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == 'O' {
                ans += i * 100 + j;
            }
        }
    }
    println!("{ans}");
}
