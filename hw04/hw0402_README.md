This project is a command-line tool to check the status of Taipei Youbike stations. It allows users to search for Youbike station information by station name, UID, or station name in Chinese.

## Features

Search by Station Name: Find Youbike stations by their English names.
Search by UID: Locate stations using their unique identifier (UID).
Search by Chinese Name: Search for stations by their Chinese names.
Requirements
CURL: Ensure you have curl installed on your system.
jq: This tool uses jq to process JSON data. Make sure it is installed.
Usage

## Install jq

If you are MacOS

```shell
brew install jq
```

If you are Ubuntu

```shell
sudo apt-get install jq
```

Compile the program using a C compiler:

```shell
gcc -o youbike_checker youbike_checker.c -lcurl
```

Run the program with the following options:

## Options

-h, --help: Show the help message.
-N <station_name>, --Name <station_name>: Search station by English name.
-U <uid>, --UID <uid>: Search station by UID.
-s <station_name>, --sna <station_name>: Search station by Chinese name.

## Examples

Show Help Message

```shell
./youbike_checker -h
```

Search by Station Name

```shell
./youbike_checker -N "Station Name"
```

Search by UID

```shell
./youbike_checker -U "1234"
```

Search by Chinese Name

```shell
./youbike_checker -s "站名"
```

## Description

The program fetches real-time Youbike station data from an online JSON source, stores it locally, and uses jq to parse and search through the data. Depending on the options provided, it will filter and display relevant information about Youbike stations.

## Functionality

Fetching Data: The program uses curl to download Youbike station data in JSON format.
Command-Line Options: It provides various options to filter and search the data.
Parsing and Displaying Results: Using jq, it parses the JSON data and displays the information based on the user's search criteria.
Error Handling
Invalid numbers or inputs are handled with appropriate error messages.
If no stations are found matching the search criteria, it notifies the user.

## Conclusion

This tool simplifies the process of checking Youbike station status in Taipei, making it easy to find stations by name, UID, or Chinese name directly from the command line. Make sure to have the required tools installed and use the appropriate command-line options to get the desired results.
