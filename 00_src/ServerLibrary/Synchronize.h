#pragma once

class ServerObj;

class Synchronize
{
public:
	Synchronize(ServerObj* serverObj);
	~Synchronize();
private:
	ServerObj * mServerObj;
};