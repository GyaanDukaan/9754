#include <iostream>
#include <cassert>
#include <memory>

// Base class for electronic device control using CRTP
template <typename Derived>
class ElectronicDeviceControl {
public:
    void turnOn() {
        static_cast<Derived*>(this)->doTurnOn();
    }

    void turnOff() {
        static_cast<Derived*>(this)->doTurnOff();
    }

    virtual ~ElectronicDeviceControl() {}
};

// LightControl class
class LightControl : public ElectronicDeviceControl<LightControl> {
private:
    bool isOn;

public:
    LightControl() : isOn(false) {}

    void doTurnOn() {
        isOn = true;
        std::cout << "Light is ON" << std::endl;
    }

    void doTurnOff() {
        isOn = false;
        std::cout << "Light is OFF" << std::endl;
    }

    bool isLightOn() const {
        return isOn;
    }

    // Rule of Five
    LightControl(const LightControl& other) : isOn(other.isOn) {}
    LightControl& operator=(const LightControl& other) {
        if (this != &other) {
            isOn = other.isOn;
        }
        return *this;
    }
    LightControl(LightControl&& other) noexcept : isOn(other.isOn) {
        other.isOn = false;
    }
    LightControl& operator=(LightControl&& other) noexcept {
        if (this != &other) {
            isOn = other.isOn;
            other.isOn = false;
        }
        return *this;
    }
    ~LightControl() = default;
};

// ThermostatControl class
class ThermostatControl : public ElectronicDeviceControl<ThermostatControl> {
private:
    bool isOn;
    int temperature;

public:
    ThermostatControl() : isOn(false), temperature(20) {}

    void doTurnOn() {
        isOn = true;
        std::cout << "Thermostat is ON" << std::endl;
    }

    void doTurnOff() {
        isOn = false;
        std::cout << "Thermostat is OFF" << std::endl;
    }

    void setTemperature(int temp) {
        if (temp >= 10 && temp <= 30) {
            temperature = temp;
            std::cout << "Thermostat temperature set to: " << temp << std::endl;
        } else {
            std::cout << "Invalid temperature. Temperature must be between 10 and 30." << std::endl;
        }
    }

    int getTemperature() const {
        return temperature;
    }

    // Rule of Five
    ThermostatControl(const ThermostatControl& other) : isOn(other.isOn), temperature(other.temperature) {}
    ThermostatControl& operator=(const ThermostatControl& other) {
        if (this != &other) {
            isOn = other.isOn;
            temperature = other.temperature;
        }
        return *this;
    }
    ThermostatControl(ThermostatControl&& other) noexcept : isOn(other.isOn), temperature(other.temperature) {
        other.isOn = false;
        other.temperature = 0;
    }
    ThermostatControl& operator=(ThermostatControl&& other) noexcept {
        if (this != &other) {
            isOn = other.isOn;
            temperature = other.temperature;
            other.isOn = false;
            other.temperature = 0;
        }
        return *this;
    }
    ~ThermostatControl() = default;
};

// SmartLockControl class
class SmartLockControl : public ElectronicDeviceControl<SmartLockControl> {
private:
    bool isLocked;

public:
    SmartLockControl() : isLocked(true) {}

    void doTurnOn() {
        isLocked = false;
        std::cout << "Smart Lock is UNLOCKED" << std::endl;
    }

    void doTurnOff() {
        isLocked = true;
        std::cout << "Smart Lock is LOCKED" << std::endl;
    }

    bool isLocked() const {
        return isLocked;
    }

    // Rule of Five
    SmartLockControl(const SmartLockControl& other) : isLocked(other.isLocked) {}
    SmartLockControl& operator=(const SmartLockControl& other) {
        if (this != &other) {
            isLocked = other.isLocked;
        }
        return *this;
    }
    SmartLockControl(SmartLockControl&& other) noexcept : isLocked(other.isLocked) {
        other.isLocked = true;
    }
    SmartLockControl& operator=(SmartLockControl&& other) noexcept {
        if (this != &other) {
            isLocked = other.isLocked;
            other.isLocked = true;
        }
        return *this;
    }
    ~SmartLockControl() = default;
};

// GarageDoorControl class
class GarageDoorControl : public ElectronicDeviceControl<GarageDoorControl> {
private:
    bool isOpen;

public:
    GarageDoorControl() : isOpen(false) {}

    void doTurnOn() {
        isOpen = true;
        std::cout << "Garage Door is OPEN" << std::endl;
    }

    void doTurnOff() {
        isOpen = false;
        std::cout << "Garage Door is CLOSED" << std::endl;
    }

    bool isOpen() const {
        return isOpen;
    }

    // Rule of Five
    GarageDoorControl(const GarageDoorControl& other) : isOpen(other.isOpen) {}
    GarageDoorControl& operator=(const GarageDoorControl& other) {
        if (this != &other) {
            isOpen = other.isOpen;
        }
        return *this;
    }
    GarageDoorControl(GarageDoorControl&& other) noexcept : isOpen(other.isOpen) {
        other.isOpen = false;
    }
    GarageDoorControl& operator=(GarageDoorControl&& other) noexcept {
        if (this != &other) {
            isOpen = other.isOpen;
            other.isOpen = false;
        }
        return *this;
    }
    ~GarageDoorControl() = default;
};

// Test cases using assert
void runTests() {
    LightControl light;
    assert(!light.isLightOn());

    light.turnOn();
    assert(light.isLightOn());

    light.turnOff();
    assert(!light.isLightOn());

    ThermostatControl thermostat;
    assert(thermostat.getTemperature() == 20);

    thermostat.setTemperature(25);
    assert(thermostat.getTemperature() == 25);

    thermostat.setTemperature(35); // Should print an error message but not change the temperature
    assert(thermostat.getTemperature() == 25);

    thermostat.turnOn();
    assert(thermostat.getTemperature() == 25); // Temperature should remain the same

    thermostat.turnOff();
    assert(thermostat.getTemperature() == 25); // Temperature should remain the same

    SmartLockControl smartLock;
    assert(smartLock.isLocked());

    smartLock.turnOn();
    assert(!smartLock.isLocked());

    smartLock.turnOff();
    assert(smartLock.isLocked());

    GarageDoorControl garageDoor;
    assert(!garageDoor.isOpen());

    garageDoor.turnOn();
    assert(garageDoor.isOpen());

    garageDoor.turnOff();
    assert(!garageDoor.isOpen());
}

int main() {
    runTests();
    std::cout << "All tests passed!" << std::endl;

    // Demonstration of using smart pointers
    std::unique_ptr<ElectronicDeviceControl<LightControl>> lightPtr = std::make_unique<LightControl>();
    std::unique_ptr<ElectronicDeviceControl<ThermostatControl>> thermostatPtr = std::make_unique<ThermostatControl>();
    std::unique_ptr<ElectronicDeviceControl<SmartLockControl>> smartLockPtr = std::make_unique<SmartLockControl>();
    std::unique_ptr<ElectronicDeviceControl<GarageDoorControl>> garageDoorPtr = std::make_unique<GarageDoorControl>();

    std::unique_ptr<ElectronicDeviceControl<LightControl>>[] devices = {
        std::move(lightPtr),
        std::move(thermostatPtr),
        std::move(smartLockPtr),
        std::move(garageDoorPtr)
    };

    for (auto& device : devices) {
        device->turnOn();
        device->turnOff();
    }

    return 0;
}
