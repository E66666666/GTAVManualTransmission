#pragma once
#include <vector>

namespace DrivingAssists {
    struct ABSData {
        bool Use;
    };

    struct TCSData {
        bool Use;
        std::vector<bool> SlippingWheels;
    };

    struct ESPData {
        bool Use;
        bool Understeer;
        // average front wheels slip angle
        float UndersteerAngle; // rad
        bool Oversteer;
        // average rear wheels slip angle
        float OversteerAngle; // rad
        bool OppositeLock;
    };

    struct LSDData {
        bool Use;
        float BrakeLF;
        float BrakeRF;
        float BrakeLR;
        float BrakeRR;
    };

    ABSData GetABS();
    TCSData GetTCS();
    ESPData GetESP();

    // Technically not an assist since the ESP-ish "braked wheel sends power to the other side"
    // doesn't apply, but putting it here anyway since we negative-brake to simulate power transfer.
    LSDData GetLSD();

    std::vector<float> GetESPBrakes(ESPData espData, LSDData lsdData);
    std::vector<float> GetTCSBrakes(TCSData tcsData, LSDData lsdData);
    std::vector<float> GetABSBrakes(ABSData absData, LSDData lsdData);
}