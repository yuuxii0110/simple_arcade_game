void laser_setup(int laser_pin){
  pinMode(laser_pin, OUTPUT);
  digitalWrite(laser_pin, 0);
}

void motor_setup(int motor_pin){
  pinMode(motor_pin, OUTPUT);
  digitalWrite(motor_pin, 0);
}
