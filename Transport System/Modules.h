#pragma once
#include "User.h"
#include "TransportManager.h"

void adminModule(User* activeSession, TransportManager& manager, User*& sessionRef);
void studentModule(User* activeSession, TransportManager& manager, User*& sessionRef);
void driverModule(User* activeSession, TransportManager& manager, User*& sessionRef);