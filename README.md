AddressBook2
=====

A command line application developed in Java programming language. The main purpose of this project is to act as a qualification test of mastering of Java.

# Note!!! (For submit your code)

 * Fork me and use pull request to submit changes to `develop` branch. Anything unclear about the feature, fire issue on github.
 * You should submit your source code and pom file
 * Remember this is the only place to submit your code, not by email. Tip: do some basic learning of github


# Requirement

Browse and modify a JSON data structure with `ls`,`cd`,`cat`, `add`, `remove`

## Must be implemented features

* Let's say we have this address entry data structure in JSON

        {
            "entries": {
                "lilei" : {
                    "age": 27,
                    "mobile" : "13700000000",
                    "address" : "Earth somewhere"
                }, 
                "hanmeimei" : {
                    "age": 26,
                    "mobile" : "13700000001",
                    "address" : "Earth somewhere else"
                }
            }
        }

* start interactive command line application

    `sh> java -jar ab.jar`

    `ab> _`
    
* use `ls` command to list the items in current position
    
    `ab> ls`

    `ab> entries`

* use `cd` command to go to the entry like go to a directory
    
    `ab> cd entries`

    `ab> ls`
    
    `ab> lilei hanmeimei`

* use `cat` command to display th item data
    
    `ab> cat lilei`

    `ab> "lilei" : { "age": 27, "mobile" : "13700000000", "address" : "Earth somewhere" }`

        
* use `add` command to add new address entry to JSON

    `ab> cd entries`

    `ab> add`

    `key: xiaoming`

    `value: { "age": 28, "mobile" : "13700000002", "address" : "Earth somewhere too" }`

    `address entry added`

    `ab> ls`
    
    `ab> lilei hanmeimei xiaoming`
    
    Note: the key should be identical, if trying to add duplicated key, just display an error message 

* use `remove` command to get one or more address entries
    
    `ab> cd entries`

    `ab> remove`

    `please give the key: xiaoming`
    
    `xiaoming was deleted from JSON`

    Note: if trying to delete an non-exist key, just display an error message 

* get help

    `ab> !help`

    then help message should be displayed, and when encoutering invalid command, help message
    should also be displayed.

* quit from the application

    `ab> !quit`

    `sh> _`

## Nonfunctional requirement

* project must be managed by [Maven](http://maven.apache.org/), latest version of v3

* unit test is a must

  * because we want to see how you test your application

* javadoc for public interface/class/method is a must

* Java code should be well-formatted

  * __NEVER__ use `tab` for indentation


* JSON should be used as backend persistent storage

  * You are welcome to use any JSON lib you want

* [`ExecutorService`](http://docs.oracle.com/javase/6/docs/api/java/util/concurrent/ExecutorService.html) should be used to handle commands

* [Maven assembly plugin](http://maven.apache.org/plugins/maven-assembly-plugin/) should be used to assemble the application as runable jar

  * `mvn clean install`, then everything should be ready, and one can find assembled application
    under `target` folder

* __DO NOT__ store any IDE specific files into git repository

* if there is any fault in this readme, please also fix it or submit an issue


