
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * It is entry point for JavaFX class and it is called by {@link RunCatapultSimulationApp}.
 * because it is recommended workaround according to https://stackoverflow.com/questions/52653836/maven-shade-javafx-runtime-components-are-missing?answertab=votes#52654791
 *   
 * 
 * @author koz01
 *
 */
public class JavaFXApplication extends Application {
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		primaryStage.setTitle("Catapult simulation application");
		CatapultSimulationController controller = CatapultSimulationController.create();
		Scene scene = controller.createScene();
		primaryStage.setScene(scene);
		primaryStage.show();
		primaryStage.setOnCloseRequest(x -> System.exit(0));
	}

	public static void doLaunch(String[] args) {
		Application.launch(args);
	}

}
