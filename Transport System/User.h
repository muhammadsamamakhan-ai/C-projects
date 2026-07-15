#pragma once
#include <string>
#include "Domain.h"

class User
{
protected:
    std::string username;
    std::string password;
    std::string roleType;

public:
    User(std::string uname, std::string pass, std::string role);
    virtual ~User();

    std::string getUsername() const;
    std::string getPassword() const;
    bool   authenticate(std::string pass) const;
    std::string getRole() const;

    virtual void displayMenu() const = 0;
    virtual void displayInfo() const = 0;
};

class Student : public User
{
private:
    std::string         studentRegNo;
    TransportPass* transportPass;

public:
    Student(std::string uname, std::string pass, std::string regNo);
    ~Student();

    void           linkTransportPass(TransportPass* pass);
    TransportPass* getPass();
    std::string    getRegNo() const;
    void           removePass();

    void displayMenu() const override;
    void displayInfo() const override;
};

class Driver : public User
{
private:
    std::string licenseId;
    std::string assignedVehicleId;

public:
    Driver(std::string uname, std::string pass, std::string license);

    void        assignVehicle(std::string vehicleId);
    std::string getAssignedVehicle() const;
    std::string getLicenseId() const;

    void displayMenu() const override;
    void displayInfo() const override;
};

class Admin : public User
{
public:
    Admin(std::string uname, std::string pass);

    void displayMenu() const override;
    void displayInfo() const override;
};