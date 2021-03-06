#include "modConfig.h"

modConfigGeneralConfigStructTypedef modConfigGeneralConfig;

modConfigGeneralConfigStructTypedef* modConfigInit(void) {
	driverSWStorageManagerConfigStructSize = (sizeof(modConfigGeneralConfigStructTypedef)/sizeof(uint16_t)); // Calculate the space needed for the config struct in EEPROM
	return &modConfigGeneralConfig;
};

bool modConfigStoreAndLoadDefaultConfig(void) {
	bool returnVal = false;
	if(driverSWStorageManagerConfigEmpty) {
		returnVal = modConfigStoreDefaultConfig();
	}
	
	modConfigLoadConfig();
	return returnVal;
};

bool modConfigStoreConfig(void) {
	return driverSWStorageManagerStoreStruct(&modConfigGeneralConfig,STORAGE_CONFIG);
	// TODO_EEPROM
};

bool modConfigLoadConfig(void) {
	return driverSWStorageManagerGetStruct(&modConfigGeneralConfig,STORAGE_CONFIG);
};

bool modConfigStoreDefaultConfig(void) {
	// VALUES WILL ONLY AUTIMATICALLY UPDATE AFTER FLASH ERASE!
	modConfigGeneralConfigStructTypedef defaultConfig;
	defaultConfig.noOfCells 																=	6;														// X Cells in series
	defaultConfig.batteryCapacity														=	11.00f;												// XXAh battery
	defaultConfig.cellHardUnderVoltage											= 2.30f;												// Worst case X.XXV as lowest cell voltage
	defaultConfig.cellHardOverVoltage												= 4.40f;												// Worst case X.XXV as highest cell voltage
	defaultConfig.cellSoftUnderVoltage											= 2.50f;												// Normal lowest cell voltage X.XXV.
	defaultConfig.cellSoftOverVoltage												= 4.25f;												// Normal highest cell voltage X.XXV.
	defaultConfig.cellBalanceDifferenceThreshold						=	0.01f;												// Start balancing @ XmV difference, stop if below.
	defaultConfig.cellBalanceStart													= 3.80f;												// Start balancing above X.XXV.
	defaultConfig.cellBalanceUpdateInterval									= 4*1000;													// Keep calculated resistors enabled for this amount of time in miliseconds.
	defaultConfig.maxSimultaneousDischargingCells						= 5;														// Allow a maximum of X cells simultinous discharging trough bleeding resistors.
	defaultConfig.timoutDischargeRetry											= 4*1000;												// Wait for X seconds before retrying to enable load.
	defaultConfig.hysteresisDischarge 											= 0.02f;												// Lowest cell should rise XXmV before output is re enabled.
	defaultConfig.timoutChargeRetry													= 30*1000;											// Wait for XX seconds before retrying to enable charger.
	defaultConfig.hysteresisCharge													= 0.01f;												// Highest cell should lower XXmV before charger is re enabled.
	defaultConfig.timoutChargeCompleted											= 30*60*1000;										// Wait for XX minutes before setting charge state to charged.
	defaultConfig.timoutChargingCompletedMinimalMismatch 		= 6*1000;												// If cell mismatch is under threshold and (charging is not allowed) wait this delay time to set "charged" state.
	defaultConfig.maxMismatchThreshold											= 0.020f;												// If mismatch is under this threshold for timoutChargingCompletedMinimalMismatch determin fully charged.
	defaultConfig.chargerEnabledThreshold										= 0.2f;													// If charge current > X.XA stay in charging mode and dont power off.
	defaultConfig.timoutChargerDisconnected									= 2000;													// Wait for X seconds to respond to charger disconnect.
	defaultConfig.minimalPrechargePercentage								= 0.80f;												// output should be at a minimal of 80% of input voltage.
	defaultConfig.timoutPreCharge														= 300;													// Precharge error timout, allow 300ms pre-charge time before declaring load error.
	defaultConfig.maxAllowedCurrent													= 120.0f;												// Allow max XXXA trough BMS.
	defaultConfig.displayTimoutBatteryDead									= 5000;													// Show battery dead symbol X seconds before going to powerdown in cell voltage error state.
	defaultConfig.displayTimoutBatteryError									= 2000;													// Show error symbol for X seconds before going to powerdown in general error state.
	defaultConfig.displayTimoutBatteryErrorPreCharge				= 20000;												// Show pre charge error for XX seconds.
	defaultConfig.displayTimoutSplashScreen									=	1000;													// Display / INIT splash screen time.
	defaultConfig.maxUnderAndOverVoltageErrorCount 					= 5;														// Max count of hard cell voltage errors.
	defaultConfig.notUsedCurrentThreshold										= 0.5f;													// If abs(packcurrent) < X.XA consider pack as not used.
	defaultConfig.notUsedTimout															= 30*60*1000;										// If pack is not used for longer than XX minutes disable bms.
	defaultConfig.stateOfChargeStoreInterval								= 60*1000;											// Interval in ms to store state of charge information.
	defaultConfig.CANID																			= 10;														// CAN ID for CAN communication.
	
	driverSWStorageManagerConfigEmpty = false;
	return driverSWStorageManagerStoreStruct(&defaultConfig,STORAGE_CONFIG);
	// TODO_EEPROM
}
