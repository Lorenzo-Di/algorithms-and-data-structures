#ifndef RECORDS_IO_H
#define RECORDS_IO_H
#include "record.h"
#include <stdio.h>

/**
 * @file records_io.h
 * @brief Manages I/O of Record struct with files
 */

/**
 * @brief Read a Record from a file.
 * @param file The open file descriptor in read mode.
 * @param record Output parameter. Must point to a valid record. On success the functions loads the data here.
 * @return 1 on success, -1 otherwise
 */
int read_record(FILE *file, Record *record);

/**
 * @brief Write a Record to a file.
 * @param file The open file descriptor in write or append mode.
 * @param record Pointer to the record to write.
 * @return 1 on success, -1 otherwise.
 */
int write_record(FILE *file, const Record *record);

/**
 * @brief Load all records from a file.
 * @param file The open file descriptor in read mode
 * @param records Output parameter. On success this is set to a newly allocated array with the loaded records.
 * @param count Output parameter. On success this is set to the number of records loaded
 * @return 1 on success, -1 otherwise
 */
int load_records_from_file(FILE *file, Record **records, size_t *count);

/**
 * @brief Save multiple records to a file
 * @param file The open file descriptor in write or append mode
 * @param records The records to save
 * @param count The number of records to save
 * @return 1 on success, -1 otherwise
 */
int save_records_to_file(FILE *file, const Record *records, size_t count);

/**
 * @brief Write a Record to stdout
 * @param record The record to write
 */
void print_record(const Record *record);

#endif /* RECORDS_IO_H */