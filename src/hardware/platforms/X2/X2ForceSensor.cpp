#include "X2ForceSensor.h"

X2ForceSensor::X2ForceSensor(int sensorID) {

    this->sensorID = sensorID;

}

void X2ForceSensor::updateInput() {

    forceReading = sensorValueToNewton(*(&CO_OD_RAM.actualSensorForces.sensor1 + sensorID));
}

bool X2ForceSensor::calibrate() {
    spdlog::debug("[X2ForceSensor::calibrate]: Force Sensor {} Zeroing", sensorID);

    std::stringstream sstream;
    char *returnMessage;

    sstream << "[1] " << 17+sensorID << " read 0x7050 255 i8";
    std::string strCommand = sstream.str();
    char *SDO_Message = (char *)(strCommand.c_str());
    cancomm_socketFree(SDO_Message, &returnMessage);
    std::string retMsg = returnMessage;
    spdlog::debug(retMsg);

    if (retMsg.find("ERROR") != std::string::npos) {
        spdlog::error("[X2ForceSensor::calibrate]: Force Sensor {} error occured during zeroing", sensorID);
        return false;
    }
    else{
        spdlog::info("[X2ForceSensor::calibrate]: Force Sensor {} succesfully zeroed.", sensorID);
        return true;
    }
}

double X2ForceSensor::getForce() {

    return forceReading;

}

double X2ForceSensor::sensorValueToNewton(int sensorValue) {

    // todo: take back angle into account
//    float scaleFactor = 0.246; // X2_A
    float scaleFactor = 0.194; // X2_B
    return (sensorValue-1500.0)*scaleFactor;

}


