#ifndef MESSAGES_H
#define MESSAGES_H
#include <QString>


const QString blackColor = "black";
const QString whiteColor = "white";
const QString greyColor = "grey";
const int actualTelemetricSize = 30;
const int devicesCount = 3;

struct Header
{
    uint32_t messageTimestamp;          // Timestamp of the message
    uint32_t transmissionStartTime;     // Start time of the transmission
    uint32_t dataId;                    // data Identifier
    uint32_t messageCount;              // Number of messages in the file
    uint32_t reserve;
    uint32_t reserve2;
    uint32_t totalFlightDuration;        // Total duration of the flight
    uint32_t flightIdentifier;           // Flight Identifier
    uint32_t eventStartPosition;         // Position of the start of event logging
    uint32_t stateVectorStartPosition;   // Position of the start of state vector logging
    uint32_t groupCompositionData;       // Data about the composition of groups
};

const QString actualNameMassive[actualTelemetricSize] = {"Packet ID","Counter", "Data ID","User No","Group No","Status A",
                                       "Power On Time","Operational Time","Data Integrity","Angle X","Angle Y","Angle Z",
                                       "Velocity X","Velocity Y","Velocity Z","Speed Magnitude","Coord X","Coord Y",
                                       "Altitude","Angular Rate X","Angular Rate Y","Angular Rate Z","Accel X","Accel Y",
                                       "Accel Z","System Time, Milliseconds","Coord A","Coord B","Altitude B",
                                       "Track Angle B"};

#pragma pack(push, 1)
struct ActualTelemetricMessage
{
    uint16_t packageIdentifier;          // Package identifier
    uint32_t counter;                    // Counter
    uint32_t missionIdentifier;          // Mission identifier
    uint8_t subscriberNumber;            // Subscriber number
    uint8_t groupNumber;                 // Group number
    uint8_t statusA;                     // Status A
    uint8_t reserveA;                    // Reserved A
    uint32_t powerOnTime;                // Power on time
    uint32_t navigationTime;             // Navigation time
    uint16_t dataValidity;               // Data validity
    int16_t rollAngle;                   // Roll angle
    int16_t pitchAngle;                  // Pitch angle
    int16_t headingAngle;                // Heading angle
    int32_t northSpeed;                  // North speed
    int32_t eastSpeed;                   // East speed
    int32_t verticalSpeed;               // Vertical speed
    uint32_t speedMagnitude;             // Speed magnitude
    int32_t latitude;                    // Latitude
    int32_t longitude;                   // Longitude
    int32_t altitude;                    // Altitude
    int16_t angularVelocityX;            // Angular velocity X
    int16_t angularVelocityY;            // Angular velocity Y
    int16_t angularVelocityZ;            // Angular velocity Z
    int16_t accelerationX;               // Acceleration X
    int16_t accelerationY;               // Acceleration Y
    int16_t accelerationZ;               // Acceleration Z
    uint32_t gpsTime;                    // GPS time since week start, milliseconds
    int32_t ssLatitude;                  // SS latitude
    int32_t ssLongitude;                 // SS longitude
    int32_t ssAltitude;                  // SS altitude
};


struct ActualUartMessage
{
    uchar headerStart;
    ushort headerAddress;
    uchar headerCode;
    ushort headerLength;
    uint16_t packageIdentifier;          // Package identifier
    uint32_t counter;                    // Counter
    uint32_t missionIdentifier;          // Mission identifier
    uint8_t subscriberNumber;            // Subscriber number
    uint8_t groupNumber;                 // Group number
    uint8_t statusA;                     // Status A
    uint8_t reserveA;                    // Reserved A
    uint32_t powerOnTime;                // Power on time
    uint32_t navigationTime;             // Navigation time
    uint16_t dataValidity;               // Data validity
    int16_t rollAngle;                   // Roll angle
    int16_t pitchAngle;                  // Pitch angle
    int16_t headingAngle;                // Heading angle
    int32_t northSpeed;                  // North speed
    int32_t eastSpeed;                   // East speed
    int32_t verticalSpeed;               // Vertical speed
    uint32_t speedMagnitude;             // Speed magnitude
    int32_t latitude;                    // Latitude
    int32_t longitude;                   // Longitude
    int32_t altitude;                    // Altitude
    int16_t angularVelocityX;            // Angular velocity X
    int16_t angularVelocityY;            // Angular velocity Y
    int16_t angularVelocityZ;            // Angular velocity Z
    int16_t accelerationX;               // Acceleration X
    int16_t accelerationY;               // Acceleration Y
    int16_t accelerationZ;               // Acceleration Z
    uint32_t gpsTime;                    // GPS time since week start, milliseconds
    int32_t ssLatitude;                  // SS latitude
    int32_t ssLongitude;                 // SS longitude
    int32_t ssAltitude;                  // SS altitude
    ushort reserved;                     // Reserved
};
#pragma pack(pop)


struct uartFile{
    uchar   hStart;
    ushort  hAddr;
    uchar   hCode;
    uint32_t  hLength;
    ushort controlSumm;
}__attribute__((packed));


struct systemFirst {
    uint16_t packetId;                   // Packet Identifier
    uint32_t timeCounter;                // Time Counter
    int32_t latitude;                    // Latitude
    int32_t longitude;                   // Longitude
    int32_t altitude;                    // Altitude
    int16_t trueHeading;                 // True Heading
    int16_t rollAngle;                   // Roll Angle
    int16_t pitchAngle;                  // Pitch Angle
    int32_t northVelocity;               // North Component of Velocity
    int32_t eastVelocity;                // East Component of Velocity
} __attribute__((packed));


const QString systemFirstNameMassive[10] = {
    "Packet Identifier",
    "Time Counter",
    "Latitude",
    "Longitude",
    "Altitude",
    "True Heading",
    "Roll Angle",
    "Pitch Angle",
    "North Component of Velocity",
    "East Component of Velocity"
};


struct systemSecond
{
    uint16_t packetId;                    // Packet Identifier
    uint32_t timeCounter;                 // Time Counter
    struct
    {
        uint8_t condition : 1;
        uint8_t ready : 1;
        uint8_t charge : 1;
        uint8_t dutyRegime : 1;
        uint8_t mainRegime : 1;
        uint8_t reserve : 3;
    } stateWordPE;

    uint8_t batteryLevel;                 // Battery Level
    uint8_t batteryCapacity;              // Remaining Capacity
    uint16_t workTime;                    // Remaining Work Time
    uint8_t timeToReadyPE;                // Time to Ready for Main Work
    uint16_t givenElectricity;            // Current Delivered to Consumer
    uint8_t voltage;                      // Power Supply Voltage
} __attribute__((packed));


const QString systemSecondNameMassive[10] = {
    "Packet Identifier",
    "Time Counter",
    "State Word Condition",
    "State Word Ready",
    "State Word Charge Regime",
    "State Word Duty Regime",
    "State Word Main Regime",
    "Battery Level",
    "Remaining Capacity",
    "Remaining Work Time"
};


struct systemThird
{
    uint16_t packetId;                          // Packet Identifier
    uint32_t timeCounter;                       // Time Counter
    struct
    {
        uint16_t IOS : 1;
        uint16_t take : 1;
        uint16_t regimeO : 2;
        uint16_t stateO : 2;
        uint16_t V_TK : 1;
        uint16_t signR : 1;
        uint16_t reserve : 8;
    } infoO;
    float azimuth;
   } __attribute__((packed));


const QString systemThirdNameMassive[10] = {
    "Packet Identifier",
    "Time Counter",
    "-",
    "Take",
    "O Mode",
    "O State",
    "V and TK",
    "R Sign",
    "Reserved",
    "Azimuth",
};


// Device system info page
struct deviceFirst {                         // Control Exchange Array
    uint8_t arrayId;                              // Array ID
    uint16_t messageLength;                       // Message Length
    uint32_t counter;                             // Counter
    uint8_t arrayCount;                           // Number of arrays in the message
    uint8_t hours;                                // Hours
    uint8_t minutes;                              // Minutes
    uint8_t seconds;                              // Seconds
    uint8_t groupObjectsCount;                    // Number of objects in own group
    uint8_t airObjectsCount;                      // Number of air objects in the message
    uint8_t groundObjectsCount;                   // Number of ground objects in the message
}__attribute__((packed));

const QString deviceFirstNameArray[10] = {
    "Array ID", "Message Length", "Number of Arrays in Message",
    "Hours", "Minutes", "Seconds", "Number of Objects in Own Group",
    "Number of Air Objects in Message", "Number of Ground Objects in Message",
    "Number of Arrays in Intergroup Exchange"
};


struct deviceSecond {                               // Air Object Array
    uint8_t arrayId;                              // Array ID
    uint8_t messageLength;                        // Message Length
    int32_t latitude;                             // Latitude (offset from reference point)
    int32_t longitude;                            // Longitude (offset from reference point)
    uint32_t barometricHeight;                    // Barometric height
    uint32_t geodesicHeight;                      // Geodesic height
    int32_t trueSpeed;                            // True speed
    int32_t trackSpeed;                           // Track speed
    uint16_t heading;                             // True heading
    uint16_t trackAngle;                          // Track angle
}__attribute__((packed));

const QString deviceSecondNameArray[10] = {
    "Array ID", "Message Length", "Latitude (offset)",
    "Longitude (offset)", "Barometric Height", "Geodesic Height",
    "True Speed", "Track Speed", "True Heading",
    "Track Angle"
};


struct deviceThird {                         // Potential Object Array
    uint8_t arrayId;                              // Array ID
    uint8_t messageLength;                        // Message Length
    uint8_t batteryStatus;                        // Battery status
    uint16_t flightRange;                         // Flight range
    uint8_t payloadType;                          // Payload type
    uint8_t sensorType;                           // Sensor type
    uint8_t taskCompletionStatus;                 // Task completion status
    uint8_t systemFailures;                       // System failures
    uint8_t ownObjectNumber;                      // Own object number
    uint8_t objectSerialNumber;                   // Object serial number
}__attribute__((packed));

const QString deviceThirdNameArray[10] = {
    "Array ID", "Message Length", "Battery Status",
    "Flight Range", "Payload Type", "Sensor Type",
    "Task Completion Status", "System Failures",
    "Own Object Number", "Object Serial Number"
};


struct PacketReader
{
    deviceFirst deviceFirstStruct;
    deviceSecond deviceSecondStruct;
    deviceThird deviceThirdStruct;
    char array[4];
};



#endif // MESSAGES_H
