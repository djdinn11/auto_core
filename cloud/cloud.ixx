/*!
\file cloud.ixx
\brief This connects to a Google Cloud server.
*/
export module cloud;
import visual;
import <cpr/cpr.h>;

string firebase_url = "https://auto-core-cloud-default-rtdb.firebaseio.com/star.json";

string remove_first_and_last_quotation_mark(const string& input) {
    if (!input.empty() && input[0] == '"' && input[input.length() - 1] == '"') {
        return remove_first_and_last_char(input);
    }
    return input;
}

string append_first_and_last_quotation_mark(const string& input) {
    return format("\"{}\"", input);
}

export void get_string_from_firebase() {
    auto response = cpr::Get(cpr::Url {firebase_url});
    if (response.status_code != cpr::status::HTTP_OK) {
        print("HTTP GET Request failed with status: {}", response.status_code);
    }
    else {
        logg("Retrieved data: {}", remove_first_and_last_quotation_mark(response.text));
    }
}

export void update_string_in_firebase(const string& value) {
    string value_with_quotes = append_first_and_last_quotation_mark(value);
    auto response = cpr::Put(cpr::Url {firebase_url},
        cpr::Body {value_with_quotes},
        cpr::Header {{"Content-Type", "application/json"}});
    if (response.status_code != cpr::status::HTTP_OK) {
        print("HTTP PUT Request failed with status: {}", response.status_code);
    }
    else {
        logg("Updated data: {}", remove_first_and_last_quotation_mark(response.text));
    }
}
