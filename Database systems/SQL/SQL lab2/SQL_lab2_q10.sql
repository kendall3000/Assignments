/*10) Which books are most popular? Create a query that displays the book number, the book title, 
and the number of times each book has been checked out. Arrange the books in order from the most checkouts to 
the fewest checkouts. For books with the same number of checkouts, arrange alphabetically.*/

SELECT BOOK.BOOK_NUM, BOOK.BOOK_TITLE, COUNT(CHECKOUT.CHECK_NUM) AS NUM_OF_CHECKOUTS
FROM BOOK
LEFT JOIN CHECKOUT ON BOOK.BOOK_NUM = CHECKOUT.BOOK_NUM
GROUP BY BOOK.BOOK_NUM, BOOK.BOOK_TITLE 
ORDER BY NUM_OF_CHECKOUTS desc, BOOK.BOOK_TITLE;


