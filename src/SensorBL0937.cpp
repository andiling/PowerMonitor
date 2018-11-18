#include "PowerMonitor.h"

#ifdef KOOGEEK_P1EU

HLW8012 PowerSensor::bl0937 = HLW8012();

void PowerSensor::begin() {
    bl0937.begin(CF_PIN, CF1_PIN, SEL_PIN, LOW);
    bl0937.setResistors(0.001, 2350000, 1000);
    bl0937.setPowerMultiplier(3414290);
    bl0937.setCurrentMultiplier(25740);
    bl0937.setVoltageMultiplier(313400);

    attachInterrupt(digitalPinToInterrupt(CF_PIN), cfInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CF1_PIN), cf1Interrupt, FALLING);
    lastSwitch = 0;
}

void PowerSensor::loop() {
    if (millis() - lastSwitch > 1000) {
        power = bl0937.getActivePower();
        voltage = bl0937.getVoltage();
        current = bl0937.getCurrent() * 1000;
        // bl0937.toggleMode();
        lastSwitch = millis();
    }
}

void ICACHE_RAM_ATTR PowerSensor::cfInterrupt() {
    bl0937.cf_interrupt();
}

void ICACHE_RAM_ATTR PowerSensor::cf1Interrupt() {
    bl0937.cf1_interrupt();
}

PowerSensor powerSensor = PowerSensor();

#endif