#ifndef ALIPP13NONLINEARITYSELECTION_H
#define ALIPP13NONLINEARITYSELECTION_H

// --- Custom header files ---
#include "AliPP13PhotonSelectionMC.h"
#include "AliPP13SelectionWeights.h"
#include "AliPP13DetectorHistogram.h"

// --- ROOT system ---
#include <TObjArray.h>
#include <TList.h>

// --- AliRoot header files ---
#include <AliVCaloCells.h>
#include <AliVCluster.h>
#include <AliLog.h>

// TODO: Merge nonlinearity selection wiht nonlinearity Study
//

class AliPP13NonlinearitySelection: public AliPP13PhotonSelectionMC
{
public:
	AliPP13NonlinearitySelection():
		AliPP13PhotonSelectionMC(),
		fMassPt()
	{
	}

	AliPP13NonlinearitySelection(const char * name, const char * title, 
		AliPP13ClusterCuts cuts, AliPP13SelectionWeights * w, Bool_t isMC = kTRUE):
		AliPP13PhotonSelectionMC(name, title, cuts, w),
		fMassPt()
	{
		// NB: Disable timing cuts for MC
		if(isMC)
			fCuts.fTimingCut = 999999;
	}

	virtual void InitSelectionHistograms();

	~AliPP13NonlinearitySelection()
	{
		for(Int_t i = 0; i < 2; ++i)
		{
			if(fMassPt[i])
				delete fMassPt[i];
		}
	}
	
protected:
	virtual void SelectTwoParticleCombinations(const TObjArray & photonCandidates, const EventFlags & flags);
	virtual void ConsiderPair(const AliVCluster * c1, const AliVCluster * c2, const EventFlags & eflags);

	AliPP13NonlinearitySelection(const AliPP13NonlinearitySelection &);
	AliPP13NonlinearitySelection & operator = (const AliPP13NonlinearitySelection &);

private:
	AliPP13DetectorHistogram * fMassPt[2]; //!
	ClassDef(AliPP13NonlinearitySelection, 2)
};
#endif