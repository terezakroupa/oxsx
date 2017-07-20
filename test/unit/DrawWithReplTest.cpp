#include <catch.hpp>
#include <OXSXDataSet.h>
#include <DataSetGenerator.h>
#include <iostream>
#include <typeinfo>
#include <numeric>

TEST_CASE("Random drawing with replacement"){

  //create events in 2 fake datasets
  OXSXDataSet testDataSet1;
  OXSXDataSet testDataSet2;
  int eventsInDataSets = 3;
  std::vector<double> eventObs1(4);
  std::vector<double> eventObs2(4);

  for(unsigned i = 0; i < eventsInDataSets; i++){
    for(size_t j = 0; j < eventObs1.size(); j++){
      eventObs1[j] = j+eventsInDataSets*i +1;
      eventObs2[j] = (-1)*eventObs1[j];
    }
    testDataSet1.AddEntry(Event(eventObs1));
    testDataSet2.AddEntry(Event(eventObs2));
  }

  //create dataset generator
  DataSetGenerator gen;
  std::vector<DataSet*> sets;
  sets.push_back(&testDataSet1);
  sets.push_back(&testDataSet2);
  gen.SetDataSets(sets);

  std::vector<double> rates;
  rates.push_back(2.0);
  rates.push_back(3.0);
  gen.SetExpectedRates(rates);
  
  //create new dataset
  gen.SetBootstrap(true);
  OXSXDataSet newDataSet = gen.ExpectedRatesDataSet();

  //get number of events remaining in original datasets
  std::vector<OXSXDataSet*> remainders = gen.AllRemainingEvents();   
  size_t remainingEvents = 0;
  for (std::vector<OXSXDataSet*>::iterator i = remainders.begin(); i != remainders.end(); ++i) {  
    OXSXDataSet* remainder = *i;
    remainingEvents+= remainder->GetNEntries();
  }


  SECTION("Correct number of events drawn with replacement"){
    REQUIRE(newDataSet.GetNEntries() == std::accumulate(rates.begin(), rates.end(), 0));
  }

  SECTION("Correct number of events left in datasets, with replacement"){
    REQUIRE(remainingEvents == 2*eventsInDataSets);
  }
  
}
