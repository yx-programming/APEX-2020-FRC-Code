use wpilib::RobotBase;

fn main() {
    let robot = RobotBase::new().expect("HAL FAILED");

    // Setup
    
    RobotBase::start_competition();

    // In match code
}
