# **APEX Robotics 2020 Season Code**
This is APEX Robotics' 2020 Season Code, writen in [Rust](https://www.rustlang.org) with the [First Rust Competition](https://github.com/first-rust-competition/first-rust-competition) library.

## Why Rust?
We chose Rust this year for a few reasons:
* It is [**fast**](https://benchmarksgame-team.pages.debian.net/benchmarksgame/fastest/rust-gpp.html), comparable to C/C++ performance
* It is (mostly) **memory safe**, with a **helpful compiler**
* **Safe threading is enforced**, allowing us to utilize all of the processing power of the RoboRIO
* The FRC libraries are **significantly smaller**, if slightly less featured (compared to WPIlib)

## How to Build

The C HAL is already included in the project, so to **build** for a RoboRIO you need to run `rustup target add arm-unknown-linux-gnueabi`, and then `cargo build` should build the code.

If you want to **deploy** the code to a RoboRIO for testing, you need to run `cargo install cargo-frc` to install the deployer, and then run `cargo frc deploy` to deploy to a robot.
> Note: for this to work properly, you will have to edit metadata in `cargo.toml`, check out [cargo-frc](https://crates.io/crates/cargo-frc) for more details.
