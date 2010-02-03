/*$Id$*/

/*
 * ParserFormat-test.cpp
 *
 * This tests the parser on different MGF examples, with a focus on data files
 * that used to break the parsing process.
 *
 * Copyright (c) 2010 Marc Kirchner <marc.kirchner@childrens.harvard.edu>
 *
 */

#include <fstream>
#include <string>

#include "mgfpunittest.h"
#include <mgfp/mgfp.h>

using namespace vigra;

struct ParserFormatTestSuite : vigra::test_suite {
    ParserFormatTestSuite() : vigra::test_suite("ParserFormat") {
        add(testCase(&ParserFormatTestSuite::testNumberFormats));
    }

    void testNumberFormats() {
        std::string file(testDataDir + "/numberformats.mgf");
        std::ifstream ifs(file.c_str());
        if (!ifs) {
            failTest("Could not open test data file.");
        }
        // prepare the parser
        mgf::Context context;
        mgf::Driver driver(context);
        // don't need verbose output for the tests
        driver.trace_parsing = false;
        driver.trace_scanning = false;

        // parse input into memory
        bool result = driver.parse_stream(ifs);
        if (!result) {
            failTest("Parsing failed. Use the mgfvalidate application with "
                     "the verbose switch to determine the cause of the error.");
        }
        // check the data
        shouldEqual(context.mgfFile.size(), static_cast<size_t>(1));
        mgf::MgfSpectrum& s = context.mgfFile[0];
        shouldEqual(s.size(), 9);
        double spectrum[9][2] = {
            {232.1765,190.9556},
            {233.1055,212.1309},
            {261.3891,218.4117},
            {275.1903,482.2604},
            {285.1643,1.324E+06},
            {288.1907,0.0215},
            {320.1273,552.8523},
            {335.1647,274.4893},
            {342.2788,218.6740}};
        for (size_t i = 0; i < 9; ++i) {
            shouldEqual(s[i].first, spectrum[i][0]);
            shouldEqual(s[i].second, spectrum[i][1]);
        }
        shouldEqual(s.getCHARGE().size(), static_cast<size_t>(1));
        shouldEqual(s.getCHARGE()[0], 4);
        shouldEqual(s.getPEPMASS().first, 508.7576);
        shouldEqual(s.getPEPMASS().second, 0.0);
        shouldEqual(s.getTITLE(), "MGFp format test");
    }
};

int main()
{
    ParserFormatTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

