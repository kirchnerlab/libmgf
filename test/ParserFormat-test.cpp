/*
 * ParserFormat-test.cpp
 *
 * This tests the parser on different MGF examples, with a focus on data files
 * that used to break the parsing process.
 *
 * Copyright (c) 2010 Marc Kirchner
 *
 */

#include <fstream>
#include <string>

#include "libmgfunittest.h"
#include <mgf/mgf.h>

using namespace vigra;

struct ParserFormatTestSuite : vigra::test_suite {
    ParserFormatTestSuite() : vigra::test_suite("ParserFormat") {
        add(testCase(&ParserFormatTestSuite::testNumberFormats));
        add(testCase(&ParserFormatTestSuite::testTitleFormats));
    }

    void testNumberFormats() {
        std::string file(testDataDir + "/numberformats.mgf");
        std::ifstream ifs(file.c_str());
        if (!ifs) {
            failTest("Could not open test data file.");
        }
        // prepare the parser
        mgf::MgfFile mgfFile;
        mgf::Driver driver(mgfFile);
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
        shouldEqual(mgfFile.size(), static_cast<size_t>(1));
        mgf::MgfSpectrum& s = mgfFile[0];
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
    
    void testTitleFormats() {
        std::string file(testDataDir + "/titleformats.mgf");
        std::ifstream ifs(file.c_str());
        if (!ifs) {
            failTest("Could not open test data file.");
        }
        // prepare the parser
        mgf::MgfFile mgfFile;
        mgf::Driver driver(mgfFile);
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
        shouldEqual(mgfFile.size(), static_cast<size_t>(4));
        shouldEqual(mgfFile[0].getTITLE(), "Normal Title");
        shouldEqual(mgfFile[1].getTITLE(), "5.1arting with a fractional number");
        shouldEqual(mgfFile[2].getTITLE(), "=repeating the = sign");
        shouldEqual(mgfFile[3].getTITLE(), "     5paces! And other stuff: +_)(*&^%$#@!~`{}[]:\";'<>,./?=");
    }
};

int main()
{
    ParserFormatTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

