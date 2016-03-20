#include <catch.hpp>
#include <EventData.h>
#include <EventScale.h>

TEST_CASE("Simple scale on variable number 3"){
    EventScale scaler;
    scaler.SetDataRep(DataRepresentation(3));
    scaler.SetScale(2);

    // make fake event
    std::vector<double> fakeObservations;
    fakeObservations.push_back(0);
    fakeObservations.push_back(1);
    fakeObservations.push_back(2);
    fakeObservations.push_back(3);

    EventData inData(fakeObservations);
    
    // apply the shift
    EventData outData = scaler(inData);
    std::vector<double> modifiedObs = outData.GetData();

    // Check the values
    std::vector<double> correctVals = fakeObservations;
    correctVals[3] *= 2;

    REQUIRE(modifiedObs == correctVals);
}
