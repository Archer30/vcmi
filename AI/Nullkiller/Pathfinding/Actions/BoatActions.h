/*
* BoatActions.h, part of VCMI engine
*
* Authors: listed in file AUTHORS in main folder
*
* License: GNU General Public License v2.0 or later
* Full text of license available in license.txt file, in main folder
*
*/

#pragma once

#include "SpecialAction.h"
#include "../../../../lib/mapObjects/MapObjects.h"

namespace NKAI
{

namespace AIPathfinding
{
	class VirtualBoatAction : public SpecialAction
	{
	};
	
	class SummonBoatAction : public VirtualBoatAction
	{
	public:
		void execute(const CGHeroInstance * hero) const override;

		virtual void applyOnDestination(
			const CGHeroInstance * hero,
			CDestinationNodeInfo & destination,
			const PathNodeInfo & source,
			AIPathNode * dstMode,
			const AIPathNode * srcNode) const override;

		bool canAct(const AIPathNode * source) const override;

		const ChainActor * getActor(const ChainActor * sourceActor) const override;

		std::string toString() const override;

	private:
		int32_t getManaCost(const CGHeroInstance * hero) const;
	};

	class BuildBoatAction : public VirtualBoatAction
	{
	private:
		const IShipyard * shipyard;
		const CPlayerSpecificInfoCallback * cb;

	public:
		BuildBoatAction(const CPlayerSpecificInfoCallback * cb, const IShipyard * shipyard)
			: cb(cb), shipyard(shipyard)
		{
		}

		bool canAct(const AIPathNode * source) const override;

		void execute(const CGHeroInstance * hero) const override;

		Goals::TSubgoal decompose(const CGHeroInstance * hero) const override;

		const ChainActor * getActor(const ChainActor * sourceActor) const override;

		std::string toString() const override;

		const CGObjectInstance * targetObject() const override;
	};
}

}
