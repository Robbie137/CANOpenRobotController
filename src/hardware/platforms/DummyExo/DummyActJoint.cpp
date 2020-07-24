/**
 * @file DummyActJoint.cpp
 * @author Justin Fong
 * @brief 
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "DummyActJoint.h"

#include <iostream>

#include "DebugMacro.h"

DummyActJoint::DummyActJoint(int jointID, double jointMin, double jointMax, Drive *drive) : ActuatedJoint(jointID, jointMin, jointMax, drive) {
    DEBUG_OUT("MY JOINT ID: " << this->id)
    // Do nothing else
}

bool DummyActJoint::updateValue() {
    position = ActuatedJoint::getPosition();
    velocity = ActuatedJoint::getVelocity();
    torque = ActuatedJoint::getTorque();

    return true;
}

setMovementReturnCode_t DummyActJoint::setPosition(double desiredPosition) {
    lastPositionCommand = desiredPosition;
    return ActuatedJoint::setPosition(desiredPosition);
}

setMovementReturnCode_t DummyActJoint::setVelocity(double desiredVelocity) {
    lastVelocityCommand = desiredVelocity;
    return ActuatedJoint::setVelocity(desiredVelocity);
}

setMovementReturnCode_t DummyActJoint::setTorque(double desiredTorque) {
    lastTorqueCommand = desiredTorque;
    return ActuatedJoint::setTorque(desiredTorque);
}

bool DummyActJoint::initNetwork() {
    DEBUG_OUT("Joint::initNetwork()")
    drive->start();
    if (drive->initPDOs()) {
        return true;
    } else {
        return false;
    }
}
double DummyActJoint::getPosition() {
    return position;
}
double DummyActJoint::getVelocity() {
    return velocity;
}
double DummyActJoint::getTorque() {
    return torque;
}