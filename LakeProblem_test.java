
//a simple test to see whether or not the model works. 
//copy from the MOEAFramework-2.3-Demo-Maual, Dave Hadka, 2014
//should give them the classpath


import java.io.File;
import java.io.IOException;

import org.moeaframework.Executor;
import org.moeaframework.core.NondominatedPopulation;
import org.moeaframework.core.Solution;
import org.moeaframework.core.variable.RealVariable;
import org.moeaframework.problem.ExternalProblem;

public class LakeProblem {

	public static class ExternalLakeProblem extends ExternalProblem {

		public ExternalLakeProblem() throws IOException {
			super("LakeProblem.exe");
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

	
	public static void main(String[] args) {
		//check if the executable exists
		File file = new File("./LakeProblem.exe");
				
		if (!file.exists()) {
			System.err.println("Please compile the executable by running make in the folder");
			return;
		}
		

		NondominatedPopulation result = new Executor()
				.withProblemClass(ExternalLakeProblem.class)
				.withAlgorithm("NSGAII")
				.withMaxEvaluations(10000)
				.run();
				
		//display the results
		System.out.format("Objective1  Objective2  Objective3  Objective4 %n");
		
		for (Solution solution : result) {
			System.out.format("%.4f      %.4f    %.4f     %4f\n",
					solution.getObjective(0),solution.getObjective(1),solution.getObjective(2),solution.getObjective(3));
		}
	}
	
}
