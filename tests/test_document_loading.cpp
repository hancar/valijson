#include <iostream>

#include <gtest/gtest.h>

#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validation_results.hpp>
#include <valijson/validator.hpp>

#define TEST_DATA_DIR "../tests/data"

using std::string;

using valijson::adapters::AdapterTraits;
using valijson::adapters::RapidJsonAdapter;
using valijson::utils::loadDocument;
using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::ValidationResults;

class TestValidationErrors : public ::testing::Test
{

};

TEST_F(TestValidationErrors, AllOfConstraintFailure)
{
    // Load schema document
    rapidjson::Document schemaDocument;
    ASSERT_TRUE( loadDocument(TEST_DATA_DIR "/schemas/allof_integers_and_numbers.schema.json", schemaDocument) );
    RapidJsonAdapter schemaAdapter(schemaDocument);

    // Parse schema document
    Schema schema;
    SchemaParser schemaParser;
#if VALIJSON_USE_EXCEPTIONS
    ASSERT_NO_THROW(schemaParser.populateSchema(schemaAdapter, schema));
#else
    schemaParser.populateSchema(schemaAdapter, schema);
#endif

    // Test loading of test document
    rapidjson::Document testDocument;
    ASSERT_TRUE( loadDocument(TEST_DATA_DIR "/documents/array_integers_1_2_3.json", testDocument) );
    RapidJsonAdapter testAdapter(testDocument);

    rapidjson::Document testDocument;
    ASSERT_FALSE( loadDocument(TEST_DATA_DIR "/documents/array_integers_1_2_3.invalid-json", testDocument) );
    RapidJsonAdapter testAdapter(testDocument);
}
