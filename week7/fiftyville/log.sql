-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Description of the crime scene in question
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021 AND month = 7 AND day = 28
   AND street = "Humphrey Street";

-- Interviews mentioning "bakery"
SELECT transcript
  FROM interviews
 WHERE transcript LIKE "%bakery%"
   AND year = 2021 AND month = 7 AND day = 28;

-- Bakery license plates that left from 10:15am to 10:25am
SELECT license_plate
  FROM bakery_security_logs
 WHERE year = 2021 AND month = 7 AND day = 28
   AND hour = 10 AND minute BETWEEN 15 AND 25
   AND activity = "exit";

-- ATM transaction on Leggett Street, account number and amount
SELECT account_number, amount
  FROM atm_transactions
 WHERE year = 2021 AND month = 7 AND day = 28
   AND transaction_type = "withdraw"
   AND atm_location = "Leggett Street";

-- people whose phone calls lasted less than a minute on the crime date
SELECT *
  FROM people
 WHERE phone_number
    IN (SELECT caller
          FROM phone_calls
         WHERE year = 2021 AND month = 7 AND day = 28
           AND duration < 61);

-- people with a license_plate of a car that left from 10:15am to 10:25am
SELECT *
  FROM people
 WHERE license_plate
    IN (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021 AND month = 7 AND day = 28
           AND hour = 10 AND minute BETWEEN 15 AND 25
           AND activity = "exit");

/* people with a license_plate of a car that left from 10:15am to 10:25am
and whose phone_number had a call that lasted less than a minute */
SELECT name
  FROM people
 WHERE phone_number
    IN (SELECT caller
          FROM phone_calls
         WHERE year = 2021 AND month = 7 AND day = 28
           AND duration < 61)
INTERSECT
SELECT name
  FROM people
 WHERE license_plate
    IN (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021 AND month = 7 AND day = 28
           AND hour = 10 AND minute BETWEEN 15 AND 25
           AND activity = "exit");

-- earliest flight out of Fiftyville
  SELECT *
    FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
   WHERE airports.city = "Fiftyville"
     AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour, minute
   LIMIT 1;

-- destination of the earliest flight out of Fiftyville
SELECT full_name, city
  FROM airports
 WHERE airports.id
    IN (SELECT destination_airport_id
          FROM flights
          JOIN airports ON airports.id = flights.origin_airport_id
         WHERE airports.city = "Fiftyville"
           AND year = 2021 AND month = 7 AND day = 29
      ORDER BY hour, minute
         LIMIT 1);

-- Names of people who withdrew money on the 28th July
SELECT name
  FROM people
  JOIN bank_accounts ON bank_accounts.person_id = people.id
  JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
   AND atm_transactions.transaction_type = "withdraw"
   AND atm_transactions.atm_location = "Leggett Street";

/* people with a license_plate of a car that left from 10:15am to 10:25am
and whose phone_number had a call that lasted less than a minute
and withdrew money on the 28th of July*/
SELECT name
  FROM people
 WHERE phone_number
    IN (SELECT caller
          FROM phone_calls
         WHERE year = 2021 AND month = 7 AND day = 28
           AND duration < 61)
INTERSECT
SELECT name
  FROM people
 WHERE license_plate
    IN (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021 AND month = 7 AND day = 28
           AND hour = 10 AND minute BETWEEN 15 AND 25
           AND activity = "exit")
INTERSECT
SELECT name
  FROM people
  JOIN bank_accounts ON bank_accounts.person_id = people.id
  JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
   AND atm_transactions.transaction_type = "withdraw"
   AND atm_transactions.atm_location = "Leggett Street"; --BRUCE or DIANA is the thief

-- Passengers on the earliest flight out of Fiftyville
SELECT name
  FROM people
  JOIN passengers ON passengers.passport_number = people.passport_number
  JOIN flights ON flights.id = passengers.flight_id
 WHERE flights.id
    IN (SELECT flights.id
          FROM flights
          JOIN airports ON airports.id = flights.origin_airport_id
         WHERE airports.city = "Fiftyville"
           AND year = 2021 AND month = 7 AND day = 29
      ORDER BY hour, minute
         LIMIT 1);

-- THIEF: Bruce
SELECT name
  FROM people
  JOIN passengers ON passengers.passport_number = people.passport_number
  JOIN flights ON flights.id = passengers.flight_id
 WHERE flights.id
    IN (SELECT flights.id
          FROM flights
          JOIN airports ON airports.id = flights.origin_airport_id
         WHERE airports.city = "Fiftyville"
           AND year = 2021 AND month = 7 AND day = 29
      ORDER BY hour, minute
         LIMIT 1)
INTERSECT
SELECT name
  FROM people
 WHERE phone_number
    IN (SELECT caller
          FROM phone_calls
         WHERE year = 2021 AND month = 7 AND day = 28
           AND duration < 61)
INTERSECT
SELECT name
  FROM people
 WHERE license_plate
    IN (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021 AND month = 7 AND day = 28
           AND hour = 10 AND minute BETWEEN 15 AND 25
           AND activity = "exit")
INTERSECT
SELECT name
  FROM people
  JOIN bank_accounts ON bank_accounts.person_id = people.id
  JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
   AND atm_transactions.transaction_type = "withdraw"
   AND atm_transactions.atm_location = "Leggett Street";

-- name of the person who received Bruce's phone call that lasted less than a minute: ROBIN
SELECT name
  FROM people
 WHERE people.phone_number
    IN(SELECT phone_calls.receiver
         FROM phone_calls
         JOIN people ON people.phone_number = phone_calls.caller
        WHERE year = 2021 AND month = 7 AND day = 28
          AND duration < 61 AND people.name = "Bruce");