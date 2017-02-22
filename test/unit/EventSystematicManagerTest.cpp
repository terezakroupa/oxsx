#include <catch.hpp>
#include <EventSystematicManager.h>
#include <EventScale.h>
#include <EventShift.h>
#include <EventData.h>
#include <iostream>

TEST_CASE("3 observable event, shift and scale"){
    // Create the systematics
    EventScale scaler;
    scaler.SetScale(3);

    EventShift shifter;
    shifter.SetShift(1);

    // Create a fake event
    std::vector<double> data(3, 1);
    EventData event(data);

    SECTION("Acting of different observables"){
        scaler.SetDataRep(DataRepresentation(0));
        shifter.SetDataRep(DataRepresentation(1));

        EventSystematicManager sysMan;
        sysMan.Add(&scaler);
        sysMan.Add(&shifter);

        // transform
        EventData modified = sysMan.ApplySystematics(event);

        // Test
        REQUIRE(modified.GetData().size() == 3);
        REQUIRE(modified.GetData().at(0) == 3);
        REQUIRE(modified.GetData().at(1) == 2);
        REQUIRE(modified.GetData().at(2) == 1);
    }

    SECTION("Acting on same observables"){
        // Act in the order added to sysMan
        scaler.SetDataRep(DataRepresentation(0));
        shifter.SetDataRep(DataRepresentation(0));

        EventSystematicManager sysMan;
        sysMan.Add(&scaler);
        sysMan.Add(&shifter);

        // transform
        EventData modified = sysMan.ApplySystematics(event);
        // Test
        REQUIRE(modified.GetData().size() == 3);
        REQUIRE(modified.GetData().at(0) == (1 * 3 + 1) );
        REQUIRE(modified.GetData().at(1) == 1);
        REQUIRE(modified.GetData().at(2) == 1);
    }


    SECTION("Acting on same observables - otherway around"){
        // Act in the order added to sysMan
        scaler.SetDataRep(DataRepresentation(0));
        shifter.SetDataRep(DataRepresentation(0));

        EventSystematicManager sysMan;
        sysMan.Add(&shifter);
        sysMan.Add(&scaler);

        // transform
        EventData modified = sysMan.ApplySystematics(event);

        // Test
        REQUIRE(modified.GetData().at(0) == ((1 + 1) * 3) );
    }
}
