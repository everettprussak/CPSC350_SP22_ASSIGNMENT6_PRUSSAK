# Everett Prussak
# CPSC350
# 4/29/2022
# 2368093
# prussak@chapman.edu

## http://www.cplusplus.com/forum/beginner/125878/, https://www.cplusplus.com/reference/vector/vector/clear/, https://www.techiedelight.com/inorder-tree-traversal-iterative-recursive/


## Notes about Program:     1) When Adding Faculty Member, they will have no advisees until you manually select 11 (Change Student Advisor) and make a Student switch from their old advisor to newly created advisor. 2) When a faculty is added/created and the student is manually added (option 11) to the new faculty, when rolling back this created Facutly member (deleting them) the student who has them (now deleted faculty) will be left with nobody as an advisor until allocated. 3) When a student is created, and there are no faculty in the database, then the student will be automatically given a NULL faculty until allocated with an existing faculty member. 4) When a faculty member is deleted, students that had them as their advisor, will be left with a NULL (no advisor) until option 11 is choosen to allocate a new advisor that still exists.


## Notes about studentTable and facultyTable: When starting with data, it must be in a specific format for each. For studentTable it must be: 14|Everett Prussak|Sophomore|Computer Science|3.8|24   (It should not have spaces in between the | and text or number. For another student simply have them on the next line in same format). For facultyTable the format is very similar: 21|Faculty Name|Faculty Level|Faculty Depart|14,17 (All sefl-explanatory except for the student ids must be in comma separated form for multiple students, if there are no students leave it blank but | must still be present as if there was data still coming!) Also the file name should be simplt studentTable and facultyTable, not .txt, .text, etc. Just the names.




## 