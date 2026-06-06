#include "Relic.h"

Item* Relic::clone()const
{
	return new Relic(*this);
}

Relic::Relic(const ItemData& data): Item(data)
{

}