use std::io::{self, Write};
fn main() {
    print!("Input File: ");
    io::stdout()
        .flush()
        .expect("Unable to flush the standard output!");

    let mut file_name = String::new();
    io::stdin()
        .read_line(&mut file_name)
        .expect("Unable to read the file name!");

    println!("I got: {}", file_name);
}
