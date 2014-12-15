#include "dndao.h"

DnInterfaceDao::~DnInterfaceDao()
{
    //do nothing
}


DnInterfaceDao &DnInterfaceDao::operator=(DnInterfaceDao &right)
{
    if (this == &right)
        return *this;
    this->KeyName = right.KeyName;
}


DnInterfaceDao::DnInterfaceDao(DnInterfaceDao &other)
{
    this->KeyName = other.KeyName;
}


DaoTableStudent::~DaoTableStudent()
{
    //do nothing yet
}

