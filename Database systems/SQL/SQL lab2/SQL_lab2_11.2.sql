/*11) Write a question and a query of your own that joins a minimum of three tables. Think about what information might 
be useful from this database. Describe the information you want your query to return, write the query and display the results.
*/

-- Kendall's Question
/* Can you provide a list of all books checked out by students in the "Programming" subject, along with the students' 
names and the due dates for each book? */

SELECT
	CONCAT(PATRON.PAT_FNAME, ' ', PATRON.PAT_LNAME) AS STUDENT_NAME,
    BOOK.BOOK_TITLE AS Book_Title,
    CHECKOUT.CHECK_DUE_DATE AS Due_Date
FROM PATRON
JOIN CHECKOUT ON PATRON.PAT_ID = CHECKOUT.PAT_ID
JOIN BOOK ON CHECKOUT.BOOK_NUM = BOOK.BOOK_NUM
WHERE PATRON.PAT_TYPE = 'Student' AND BOOK.BOOK_SUBJECT = 'Programming'
ORDER BY BOOK.BOOK_TITLE;
