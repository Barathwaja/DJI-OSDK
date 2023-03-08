#include "telemetry_sample.hpp"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

int 
main(int argc, char** argv)
{

  // Setup OSDK.
  LinuxSetup linuxEnvironment(argc, argv);
  Vehicle* vehicle = linuxEnvironment.getVehicle();

  if (vehicle == NULL) {
    std::cout << "Vehicle not initialized, exiting.\n";
    return -1;
  }

  // Display interactive prompt
  std::cout
    << "| Available commands:                                            |"
    << std::endl;
  std::cout
    << "| [a] Get telemetry data and print                               |\n"
    << "| [b] Select some subscription topics to print                   |\n"
    << "| [c] Get telemetry data and save to file                        |"
    << std::endl;
  char inputChar;
  std::cin >> inputChar;

  switch (inputChar) {
    case 'a':
      if (vehicle->getFwVersion() == Version::M100_31)
      {
        getBroadcastData(vehicle);
      }
      else
      {
        subscribeToData(vehicle);
      }
      break;
    case 'b':
      subscribeToDataForInteractivePrint(vehicle);
      break;
    case 'c':
      subscribeToDataAndSaveLogToFile(vehicle);
      break;
    default:
      break;
  }

  return 0;
}
