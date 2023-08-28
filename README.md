## Digital Gate Lock

This Arduino project simulates a digital gate lock system that uses a keypad for input and a servo motor to control lock/unlock actions. The project involves managing user access and providing a master key feature.

### Features

- **Keypad Input:** A 4x4 keypad is used to input digits and commands.
- **Servo Motor Control:** A servo motor physically locks and unlocks the gate.
- **LCD Display:** A 16x2 LCD display is used for user prompts and status messages.
- **User Management:** Supports up to 10 users with individual passcodes.
- **Master Key:** Allows for a master key operation for authorized users to manage other users.
- **Locking Mechanism:** The servo motor controls a locking mechanism, moving the gate between locked and unlocked states.

### Functionality

1. **Initialization:** The system sets up the keypad, LCD display, and servo motor. Initial states are defined.
2. **User Data:** Up to 10 users and their passcodes can be added and removed. The data is stored in arrays.
3. **User Input:** Users enter their ID using the keypad. The ID is used to select the corresponding user's passcode.
4. **Passcode Entry:** Once the user's ID is entered, they input their passcode using the keypad.
5. **Unlocking:** If the entered passcode matches the stored passcode for the user, the servo motor unlocks the gate.
6. **Master Key:** A master key can be used to initiate special operations. The master key can delete users or add new ones.
7. **Locking:** After a successful unlock, the gate automatically locks after a brief period.
8. **User Feedback:** The LCD display provides instructions, prompts, and error messages throughout the process.

### Usage

- Users enter their ID and passcode using the keypad to unlock the gate.
- The master key holder can perform user management operations using the master key.
- When users are added or removed, the LCD displays corresponding messages.
- If an incorrect passcode is entered, an error message is displayed.
## screenshots
![image](https://github.com/ravikumar8043/Digital-lock/assets/83626538/30be4748-ef92-41d9-8654-72c2685a9e67)
![image](https://github.com/ravikumar8043/Digital-lock/assets/83626538/4cf9c52c-1d26-4a1c-95de-91d4c8745556)
![image](https://github.com/ravikumar8043/Digital-lock/assets/83626538/c7fcde3f-9e77-4ea6-8878-bbd8355dc091)

### Components

- Arduino UNO or compatible board.
- 4x4 keypad.
- 16x2 LCD display.
- Servo motor.
- Various jumper wires and components.

### How to Use

1. Connect the keypad, LCD display, and servo motor to the Arduino board as specified.
2. Upload the code to the Arduino using the Arduino IDE.
3. Follow the LCD prompts to enter user IDs and passcodes for different operations.
4. Unlock the gate using the correct user ID and passcode.
5. Use the master key to perform user management tasks.

### Note

- Adjust the lock and unlock angles in the code to match your servo motor's specifications.
- This project demonstrates the basic principles of access control using Arduino. It can be extended and improved for real-world applications.
