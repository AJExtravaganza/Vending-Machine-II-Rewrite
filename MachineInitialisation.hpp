#pragma once

#include "VendingMachine.hpp"
#include "VM100A.hpp"
#include "VM100B.hpp"
#include "VM100C.hpp"
#include "VM100D.hpp"

#include <fstream>
#include <memory>

void MachineInitialisation(std::string filenameMachineDefs, std::string filenameProductDefs, std::vector<std::shared_ptr<VendingMachine>> &machineSet);
void productDBInit(std::istream& inputStream, std::vector<Product> &database);
