BEGIN
DISPLAY welcome message

INITIALIZE faultRecords as empty list

WHILE user has not chosen Exit
    DISPLAY menu
    INPUT choice

    IF choice = 1 THEN
        INPUT numberOfFaults
        FOR each fault from 1 to numberOfFaults
            INPUT faultID, location, faultType, voltage, current, actionTaken
            IF voltage < 0 OR current < 0 THEN
                DISPLAY "Invalid input"
            ELSE
                CLASSIFY severity
                ADD record to faultRecords
                DISPLAY fault report
            END IF
        END FOR

    ELSE IF choice = 2 THEN
        IF faultRecords empty THEN
            DISPLAY "No records"
        ELSE
            DISPLAY all faultRecords
            DISPLAY summary
        END IF

    ELSE IF choice = 3 THEN
        IF faultRecords empty THEN
            DISPLAY "No records to save"
        ELSE
            OPEN electrical_fault_report.txt
            FOR each record in faultRecords
                WRITE record details to file
            END FOR
            WRITE summary to file
            CLOSE file
            DISPLAY "Report saved"
        END IF

    ELSE IF choice = 4 THEN
        DISPLAY "Goodbye"
        EXIT loop

    ELSE
        DISPLAY "Invalid choice"
    END IF
END WHILE

END
