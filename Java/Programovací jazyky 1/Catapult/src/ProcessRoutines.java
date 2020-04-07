
public final class ProcessRoutines {
	
	private ProcessRoutines() {
	}
	
	public static void sleep(int miliseconds) {
		try {
			Thread.sleep(miliseconds);
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
		}
	}
}
