#include "ServerModel.h"
#include "IOCP.h"


ServerModel::ServerModel()
{
}
ServerModel::~ServerModel()
{
}

void ServerModel::AddUser(const User* user)
{
	return;
}

std::unique_ptr<ServerModel> ServerModel::CreateServerModel(const IOMODEL& modeltype)
{
	std::unique_ptr<ServerModel> retModel;
	switch (modeltype)
	{
		case IOMODEL::IOCP:
		{
			retModel = std::make_unique<IOCP>();
		}break;
		case IOMODEL::Select:
		{
		
		}break;
		case IOMODEL::WsaEvent:
		{

		}break;
		case IOMODEL::WsaAsync:
		{

		}break;
		case IOMODEL::Overlapped:
		{

		}break;
	default:
		break;
	}
	return std::move(retModel);
}