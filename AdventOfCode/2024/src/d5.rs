use std::{collections::{HashMap, HashSet}, fs::File, io::{BufRead, BufReader}};

fn read_lines() -> (HashMap<u32, Vec<u32>>, Vec<Vec<u32>>) {
    let input = File::open("input/d5.in").unwrap();
    let reader = BufReader::new(input);
    let mut on_rules = true;
    let mut rules = HashMap::new();
    let mut updates = Vec::new();
    for line in reader.lines() {
        let line = line.unwrap();
        if line.is_empty() {
            on_rules = false;
            continue;
        }
        if on_rules {
            let mut parts = line.split("|");
            let (a, b) = (parts.next().unwrap().parse::<u32>().unwrap(), parts.next().unwrap().parse::<u32>().unwrap());
            rules.entry(a).or_insert(Vec::new()).push(b);
        } else {
            let parts = line.split(",");
            updates.push(parts.map(|v| v.parse::<u32>().unwrap()).collect());
        }
    }
    (rules, updates)
}

fn part1(rules: &HashMap<u32, Vec<u32>>, updates: &Vec<Vec<u32>>) {
    let mut ans = 0;
    for update in updates {
        let mut seen = HashSet::new();
        let mut works = true;
        update.iter().for_each(|u| {
            if rules.contains_key(u) && rules.get(u).unwrap().iter().any(|v| seen.contains(v)) {
                works = false;
            }
            seen.insert(*u);
        });
        if works {
            ans += update[update.len()/2];
        }
    }
    println!("{}", ans);
}

fn dfs(order: &mut Vec<u32>, rules: &HashMap<u32, Vec<u32>>, seen: &mut HashSet<u32>, consider: &HashSet<u32>, u: u32) {
    if seen.contains(&u) || !consider.contains(&u) {
        return;
    }
    seen.insert(u);
    if rules.contains_key(&u) {
        for v in rules.get(&u).unwrap() {
            dfs(order, rules, seen, consider, *v);
        }
    }
    order.push(u);
}
    

fn part2(rules: &HashMap<u32, Vec<u32>>, updates: &Vec<Vec<u32>>) {
    let mut ans = 0;
    for update in updates {
        let mut seen2 = HashSet::new();
        let mut works = true;
        update.iter().for_each(|u| {
            if rules.contains_key(u) && rules.get(u).unwrap().iter().any(|v| seen2.contains(v)) {
                works = false;
            }
            seen2.insert(*u);
        });
        if works { continue; }
        let mut seen = HashSet::new();
        let mut order = Vec::new();
        for u in update {
            dfs(&mut order, rules, &mut seen, &seen2, *u);
        }
        order.reverse();
        assert!(order.len() % 2 == 1);
        ans += order[order.len()/2];
    }
    println!("{}", ans);
}

pub fn main() {
    let (rules, updates) = read_lines();
    part1(&rules, &updates);
    part2(&rules, &updates);
}
