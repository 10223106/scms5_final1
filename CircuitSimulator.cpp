#include "Menu.h"
#include "olcPixelGameEngine.h"
#include "CircuitSimulator.h"
#include "Resistor.h"
#include "VoltageDivider.h" 
#include <iomanip>  // For std::setprecision
#include <stdexcept>  // For exception handling

CircuitSimulator::CircuitSimulator() {
    sAppName = "Simple Circuit Managing System";
}

bool CircuitSimulator::OnUserCreate() {
    currentState = AppState::MENU;
    InitializeMenuState();
    return true;
}

bool CircuitSimulator::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK);

    switch (currentState) {
    case AppState::MENU:
        if (!HandleMenuState()) {  // If HandleMenuState() returns false, exit the app
            return false;  // Exit the app
        }
        break;
        if (GetKey(olc::Key::ENTER).bPressed) {
            switch (menu.GetSelectedOption()) {
            case 0:
                currentState = AppState::CREDIT;
                break;
            case 1:
                currentState = AppState::SIMULATION;
                break;
            case 2:
                currentState = AppState::VOLTAGE_DIVIDER;
                break;
            case 3:
                currentState = AppState::SERIES_PARALLEL;
                break;
            case 4: //exit
                return false;
            }
        }
        break;
    case AppState::CREDIT:
        HandleCreditState();
        break;
    case AppState::SIMULATION:
        AddText(5, 10, "This feature is not ready", olc::WHITE);
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
        }
        break;

    case AppState::VOLTAGE_DIVIDER:
        HandleVoltageDividerState();
        break;

    case AppState::SERIES_PARALLEL:
        //AddText(5, 10, "Testing entering right state", olc::WHITE);
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
        }
        break;
    }

    return true;
}

//MENU=========
void CircuitSimulator::InitializeMenuState() {
    menu.AddOption("Welcome to SCMS", { 5, 10 });

    menu.AddOption("1. Circuit Simulation", { 20, 30 });
    menu.AddOption("2. Voltage Divider", { 20, 50 });
    menu.AddOption("3. Series/Parallel Resistor", { 20, 70 });
    menu.AddOption("4. Exit", { 20, 90 });
}

bool CircuitSimulator::HandleMenuState() {
    menu.HandleInput(this);
    menu.Draw(this);

    if (GetKey(olc::Key::ENTER).bPressed) {
        switch (menu.GetSelectedOption()) {
        case 0: currentState = AppState::CREDIT; break;
        case 1: currentState = AppState::SIMULATION; break;
        case 2: currentState = AppState::VOLTAGE_DIVIDER; break;
        case 3: currentState = AppState::SERIES_PARALLEL; break;
        case 4: return false;  // Exit the app
        }
    }
    return true;
}
//CREDIT======
void CircuitSimulator::InitializeCreditState() {
    // Add CREDIT 
    AddText(5, 10, "Simple Circuit Managing System", olc::WHITE);
    AddText(20, 30, "OOP Project - ECE2023", olc::WHITE);
    AddText(20, 50, "Dang Minh Truc - 10223106", olc::WHITE);
    AddText(20, 70, "Tran Dinh Hoang Quan - 10223098", olc::WHITE);
    AddText(20, 90, "Le Nguyen Minh Thi - 17115", olc::WHITE);
    AddText(5, 110, "Press ESC to go back to menu", olc::WHITE);
}
void CircuitSimulator::HandleCreditState() {
    InitializeCreditState();
    if (GetKey(olc::Key::ESCAPE).bPressed) {
        currentState = AppState::MENU;
    }
}
//VOLTAGE DIVIDER =====
void CircuitSimulator::InitializeVoltageDividerState() {
    //AddText(10, 50, "2 Testing entering right state", olc::WHITE);
    AddText(10, 10, "Voltage Divider State Initialized", olc::WHITE);
    
}
 
void CircuitSimulator::HandleVoltageDividerState() {
    //InitializeVoltageDividerState();
    static bool isInitialized = false;
    static bool isInputComplete1 = false; //add R1
    static bool isInputComplete2 = false; //add R2
    static bool isInputComplete3 = false; //add Vin
    // Initialize once when entering the state
    if (!isInitialized) {
        
        //resistor1Input.clear();  // Reset input
        resistor1Input = "";
        resistor2Input = "";
        VoltageInput = "";
        isInitialized = true; 
        return;
    }
    else
    {
        if (!isInputComplete1)
        {
            if (GetKey(olc::Key::BACK).bPressed) {
                if (resistor1Input.size() > 0) {
                    resistor1Input.pop_back();  // Xóa ký tự cuối nếu người dùng nhấn BACKSPACE
                }
            }

            if (GetKey(olc::Key::K0).bPressed || GetKey(olc::Key::NP0).bPressed) resistor1Input += '0';
            if (GetKey(olc::Key::K1).bPressed || GetKey(olc::Key::NP1).bPressed) resistor1Input += '1';
            if (GetKey(olc::Key::K2).bPressed || GetKey(olc::Key::NP2).bPressed) resistor1Input += '2';
            if (GetKey(olc::Key::K3).bPressed || GetKey(olc::Key::NP3).bPressed) resistor1Input += '3';
            if (GetKey(olc::Key::K4).bPressed || GetKey(olc::Key::NP4).bPressed) resistor1Input += '4';
            if (GetKey(olc::Key::K5).bPressed || GetKey(olc::Key::NP5).bPressed) resistor1Input += '5';
            if (GetKey(olc::Key::K6).bPressed || GetKey(olc::Key::NP6).bPressed) resistor1Input += '6';
            if (GetKey(olc::Key::K7).bPressed || GetKey(olc::Key::NP7).bPressed) resistor1Input += '7';
            if (GetKey(olc::Key::K8).bPressed || GetKey(olc::Key::NP8).bPressed) resistor1Input += '8';
            if (GetKey(olc::Key::K9).bPressed || GetKey(olc::Key::NP9).bPressed) resistor1Input += '9';

            // Xử lý dấu chấm thập phân
            if (GetKey(olc::Key::PERIOD).bPressed && resistor1Input.find('.') == std::string::npos) {
                resistor1Input += '.';  // Thêm dấu chấm nếu chưa có
            }
            if (GetKey(olc::Key::ENTER).bPressed && !isInputComplete1) {
                isInputComplete1 = true;  // Đánh dấu đã hoàn thành nhập
            }
            AddText(0, 10, "Resistor 1 Value (Ohms): " + resistor1Input, olc::WHITE);
            if (!isInputComplete1)
                return;
        }
        else if (!isInputComplete2) 
        {
            if (GetKey(olc::Key::BACK).bPressed) {
                if (resistor2Input.size() > 0) {
                    resistor2Input.pop_back();  // Xóa ký tự cuối nếu người dùng nhấn BACKSPACE
                }
            }

            if (GetKey(olc::Key::K0).bPressed || GetKey(olc::Key::NP0).bPressed) resistor2Input += '0';
            if (GetKey(olc::Key::K1).bPressed || GetKey(olc::Key::NP1).bPressed) resistor2Input += '1';
            if (GetKey(olc::Key::K2).bPressed || GetKey(olc::Key::NP2).bPressed) resistor2Input += '2';
            if (GetKey(olc::Key::K3).bPressed || GetKey(olc::Key::NP3).bPressed) resistor2Input += '3';
            if (GetKey(olc::Key::K4).bPressed || GetKey(olc::Key::NP4).bPressed) resistor2Input += '4';
            if (GetKey(olc::Key::K5).bPressed || GetKey(olc::Key::NP5).bPressed) resistor2Input += '5';
            if (GetKey(olc::Key::K6).bPressed || GetKey(olc::Key::NP6).bPressed) resistor2Input += '6';
            if (GetKey(olc::Key::K7).bPressed || GetKey(olc::Key::NP7).bPressed) resistor2Input += '7';
            if (GetKey(olc::Key::K8).bPressed || GetKey(olc::Key::NP8).bPressed) resistor2Input += '8';
            if (GetKey(olc::Key::K9).bPressed || GetKey(olc::Key::NP9).bPressed) resistor2Input += '9';

            // Xử lý dấu chấm thập phân
            if (GetKey(olc::Key::PERIOD).bPressed && resistor2Input.find('.') == std::string::npos) {
                resistor2Input += '.';  // Thêm dấu chấm nếu chưa có
            }
            if (GetKey(olc::Key::ENTER).bPressed && !isInputComplete2) {
                isInputComplete2 = true;  // Đánh dấu đã hoàn thành nhập
            }
            AddText(0, 10, "Resistor 1 Value (Ohms): " + resistor1Input, olc::WHITE);
            AddText(0, 30, "Resistor 2 Value (Ohms): " + resistor2Input, olc::WHITE);
            if (!isInputComplete2)
                return;
        }
        else if (!isInputComplete3)
        {
            if (GetKey(olc::Key::BACK).bPressed) {
                if (resistor2Input.size() > 0) {
                    resistor2Input.pop_back();  // Xóa ký tự cuối nếu người dùng nhấn BACKSPACE
                }
            }

            if (GetKey(olc::Key::K0).bPressed || GetKey(olc::Key::NP0).bPressed) VoltageInput += '0';
            if (GetKey(olc::Key::K1).bPressed || GetKey(olc::Key::NP1).bPressed) VoltageInput += '1';
            if (GetKey(olc::Key::K2).bPressed || GetKey(olc::Key::NP2).bPressed) VoltageInput += '2';
            if (GetKey(olc::Key::K3).bPressed || GetKey(olc::Key::NP3).bPressed) VoltageInput += '3';
            if (GetKey(olc::Key::K4).bPressed || GetKey(olc::Key::NP4).bPressed) VoltageInput += '4';
            if (GetKey(olc::Key::K5).bPressed || GetKey(olc::Key::NP5).bPressed) VoltageInput += '5';
            if (GetKey(olc::Key::K6).bPressed || GetKey(olc::Key::NP6).bPressed) VoltageInput += '6';
            if (GetKey(olc::Key::K7).bPressed || GetKey(olc::Key::NP7).bPressed) VoltageInput += '7';
            if (GetKey(olc::Key::K8).bPressed || GetKey(olc::Key::NP8).bPressed) VoltageInput += '8';
            if (GetKey(olc::Key::K9).bPressed || GetKey(olc::Key::NP9).bPressed) VoltageInput += '9';

            // Xử lý dấu chấm thập phân
            if (GetKey(olc::Key::PERIOD).bPressed && VoltageInput.find('.') == std::string::npos) {
                VoltageInput += '.';  // Thêm dấu chấm nếu chưa có
            }
            if (GetKey(olc::Key::ENTER).bPressed && !isInputComplete3) {
                isInputComplete3 = true;  // Đánh dấu đã hoàn thành nhập
            }
            AddText(0, 10, "Resistor 1 Value (Ohms): " + resistor1Input, olc::WHITE);
            AddText(0, 30, "Resistor 2 Value (Ohms): " + resistor2Input, olc::WHITE);
            AddText(0, 50, "Input Voltage Value (Volt) : " + VoltageInput, olc::WHITE);
            if (!isInputComplete3)
                return;
        }
    } 
    AddText(0, 10, "Resistor 1 Value (Ohms): " + resistor1Input, olc::WHITE);
    AddText(0, 30, "Resistor 2 Value (Ohms): " + resistor2Input, olc::WHITE);
    AddText(0, 50, "Input Voltage Value (Volt) : " + VoltageInput, olc::WHITE);
    AddText(0, 90, "Voltage Divider Calculation", olc::WHITE);
    //VOLTAGE DIVIDER CALCULATION
    resistor1Value = convertToDouble(resistor1Input); // Convert to double
    resistor2Value = convertToDouble(resistor2Input);  
    VinValue = convertToDouble(VoltageInput);       
    VoutValue = VinValue * (resistor2Value / (resistor1Value + resistor2Value)); 
    AddText(0, 110, "Output Voltage : " + std::to_string(VoutValue) +" V", olc::WHITE);
    //resistor1Value = std::stod(resistor1Input);  // Convert to double 
    //resistor1Value += 1.0;
    //AddText(0, 110, std::to_string(resistor1Value), olc::WHITE); 
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            delete voltageDivider;  // Clean up memory
            //voltageDivider = nullptr;  // Avoid dangling pointer
            currentState = AppState::MENU;
            isInitialized = false;  // Reset initialization
        }
        //return;
    
}
//CONVERT STRING TO DOUBLE
double CircuitSimulator::convertToDouble(const std::string& input) {
    try {
        return std::stod(input);  // Convert to double
    }
    catch (const std::invalid_argument& e) {
        // Handle invalid argument
        return 0.0;  // Return 0.0 in case of invalid input
    }
    catch (const std::out_of_range& e) {
        // Handle out of range exception
        return 0.0;  // Return 0.0 in case of out-of-range input
    }
}

//FOR LAYOUT ==========
void CircuitSimulator::AddText(float x, float y, const std::string& text, olc::Pixel color) {
    float scale = 0.8f; // Adjust this value to make text smaller
    DrawStringDecal({ x, y }, text, color, { scale, scale }); // Scale text by 0.5 
}