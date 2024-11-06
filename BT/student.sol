// SPDX-License-Identifier: MIT
pragma solidity >= 0.7.0;

contract Student_management{

	struct Student{
		int stud_id;
		string Name;
		string Department;
	}

	Student[] Students;

	function add_stud(int stud_id, string memory Name, string memory Department) public{
		Student memory stud = Student(stud_id, Name, Department);
		Students.push(stud);
	}

	function getStudent(int stud_id) public view returns(string memory, string memory){
		for(uint i = 0; i < Students.length; i++){
			Student memory stud = Students[i];
			if(stud.stud_id == stud_id){
				return(stud.Name, stud.Department);
			}
		}
        return("Name Not Found", "Department Not Found");
	}

    event log(string func);
	//Fallback Function
	fallback() external payable{
        emit log("we are in fallback" , gasleft(););
		Students.push(Student(7, "XYZ", "Mechanical"));
	}
    receive() external payable { 
        emit log("we are in receive" , gasleft(););
    }

    // Fallback
// The fallback function in Solidity is a special function that is executed when a contract 
// receives Ether along with a call to a function that does not exist in the contract, or 
// if no data is supplied with the transaction. This function must be marked as payable if 
// you want the contract to be able to receive Ether in this way.The fallback function is a 
// catch-all function that can be used when no other function matches the function signature 
// in the call or when the contract receives plain Ether without any data. However, it’s important 
// to note that fallback functions are often more expensive in terms of gas costs because their
//  execution requires more computational steps.

// receive 
// This function is triggered when a contract receives plain Ether (without data).
//  This function must also be marked as payable.

// Here’s an example of a receive function:

// receive() external payable {
//     // This function is executed when a contract receives plain Ether (without data)
// }
// The receive the function is specifically designed to handle situations where a contract is meant to
//  directly receive Ether without any additional data or function calls. It provides a more explicit 
//  and readable way to handle such transactions and is more gas-efficient than the fallback function.

    // receive cant take data in form of bytes
}