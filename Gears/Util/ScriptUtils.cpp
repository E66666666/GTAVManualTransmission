#include "ScriptUtils.h"

#include "MathExt.h"
#include <inc/natives.h>
#include <format>

void Controls::SetControlADZ(eControl control, float value, float adz) {
    PAD::_SET_CONTROL_NORMAL(0, control, sgn(value) * adz + (1.0f - adz) * value);
}

bool Util::PlayerAvailable(Player player, Ped playerPed) {
    if (!PLAYER::IS_PLAYER_CONTROL_ON(player) ||
        PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE) ||
        CUTSCENE::IS_CUTSCENE_PLAYING() ||
        !ENTITY::DOES_ENTITY_EXIST(playerPed) ||
        ENTITY::IS_ENTITY_DEAD(playerPed, 0)) {
        return false;
    }
    return true;
}

bool Util::VehicleAvailable(Vehicle vehicle, Ped playerPed) {
    return vehicle != 0 &&
        ENTITY::DOES_ENTITY_EXIST(vehicle) &&
        PED::IS_PED_SITTING_IN_VEHICLE(playerPed, vehicle) &&
        playerPed == VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 0);
}

bool Util::IsPedOnSeat(Vehicle vehicle, Ped ped, int seat) {
    Vehicle pedVehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
    return vehicle == pedVehicle &&
        VEHICLE::GET_PED_IN_VEHICLE_SEAT(pedVehicle, seat, 0) == ped;
}
