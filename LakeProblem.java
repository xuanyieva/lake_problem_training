
//this is a link between the external lake problem with the MOEAFramework.
import java.io.File;
import java.io.IOException;

import org.moeaframework.Executor;
import org.moeaframework.core.NondominatedPopulation;
import org.moeaframework.core.Solution;
import org.moeaframework.core.variable.RealVariable;
import org.moeaframework.problem.ExternalProblem;

public class LakeProblem extends ExternalProblem {

		public LakeProblem() throws IOException {
			super("./LakeProblem.exe");//run in the cube, it should be put into an "examples" foulder: ./examples/LakeProblem.exe
		}

		@Override
		public String getName() {
			return "LakeProblem";
		}

		@Override
		public int getNumberOfVariables() {
			return 100;
		}

		@Override
		public int getNumberOfObjectives() {
			return 4;
		}

		@Override
		public int getNumberOfConstraints() {
			return 1;
		}

		@Override
		public Solution newSolution() {
			Solution solution = new Solution(getNumberOfVariables(), 
					getNumberOfObjectives(),getNumberOfConstraints());

			for (int i = 0; i < getNumberOfVariables(); i++) {
				solution.setVariable(i, new RealVariable(0.0, 0.1));
			}

			return solution;
		}
		
	}
	

