
#### This Repository Consists of my own Circuit Simulator which is designed in C language using Compiler tools like Lex and Yacc.

Project Goal:
> The main aim of this project is to build a full-fledged circuit simulator which can which can parse a given
circuit and do the analysis of it. The project focuses on analyzing the circuit containing passive as well
as active elements including dependent and independent sources to find all the nodal voltages as well as
the currents. We would also be extending if possible to do DC and transient analysis of the given circuit
and if the time permits, we would be looking to solve a circuit with non-linear elements as well.

Progress made by Far :

> Phase 1: 
- Studied and understood the working of Lex and Yacc.
- Built a simple calculator with the help of Lex and Yacc.
- Parsed the Netlist file with the help of Lex and sent the tokens to Yacc file.
- A logic is written to store the parsed data from the Netlist file (with all the node information)
dynamically into linked list data structure.

> Phase 2:
- Improved the Lex rules and Yacc grammar so that the floating point numbers in the spice file can
also be parsed.
- Removed the Linked list Data structure and introduced the Hash Table as the base Data structure
to store the data of parsed Nodes from the Netlist File.
- Used the Modified Nodal Analysis algorithm to form the MNA Matrix (Normal Implementation
with zero element stamps).
- Succeeded in Implementing the Sparse Matrix(Zero element Stamps are removed) formation
using a Table chained with a linked list to store the element stamps and Modified the entire
Gaussian Elimination logic to Support my data structure.
- Implemented the Gaussian Elimination technique, using Partial Pivoting method to solve the
Equations and to find the Voltages at Nodes and Currents through the Voltage Sources in the
circuit.
- Extended the Simulator to support .op, .dc sweep operation for the resistive elements connected
to independent voltage sources and independent current sources.
- Integrated my simulator with the gschem and gnetlist which are an Open source schematic editor
and Open source Netlist generator using a Bash shell Script.

Features of my simulator:
- Floating Point resistor Values.
- Check for Inconsistency Solution (Gaussian Elimination).
- Check for the Circuits that can lead to a Zero pivot Element in Gaussian Elimination.
- Check for No Solution.
- Check for Closed or Open Circuit.
- DC Sweep with a floating Point Step Value.
