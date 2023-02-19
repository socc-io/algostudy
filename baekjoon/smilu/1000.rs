
fn main() {
    let stdin = std::io::stdin();
    
    let mut line = String::new();
    stdin.read_line(&mut line)
        .unwrap();

    let answer = line.trim()
        .split_whitespace()
        .map(|x| x.parse::<i32>().unwrap())
        .sum::<i32>();

    println!("{}", answer);
}

