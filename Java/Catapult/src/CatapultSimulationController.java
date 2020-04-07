
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javafx.application.Platform;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
/**
 * Main UI class that handles events and coordinates the whole functionality.
 * @author koz01
 *
 */
public class CatapultSimulationController {

	@FXML
	private Canvas canvas;

	@FXML
	private BorderPane root;

	@FXML
	private Slider power;
	
	@FXML
	private Slider angle;

	@FXML
	private Button fire;

	@FXML
	private Slider len;

	@FXML
	private MenuItem itemAbout;

	private Catapult catapult;

	private Ball ball;

	private Physics physics;

	private int xOfCatapult;

	private int yOfCatapult;

	private ObjectManager objectManager;

	public static CatapultSimulationController create() throws IOException {
		FXMLLoader loader = new FXMLLoader(
				CatapultSimulationController.class.getResource("CatapultSimulationPanel.fxml"));
		loader.load();
		CatapultSimulationController result = loader.getController();
		result.init();
		return result;
	}

	public Scene createScene() {
		return new Scene(root, 450, 540);
	}
	
	public void needsRedraw() {
		Platform.runLater(this::redraw);
	}

	private void angleChanged(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
		catapult.setAngle((int) angle.getValue());
		redraw();
	}

	private void lenChanged(ObservableValue<? extends  Number> observable, Number oldValue, Number newValue) {
		catapult.setLen((int) len.getValue());
		redraw();
	}
	
	private void powerChanged(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
		catapult.setPower((int) power.getValue());
	}

	private void firePressed(ActionEvent e) {
		fire.setDisable(true);
		new Thread(this::doBallMovement).start();
	}

	private void doBallMovement() {
		catapult.shootBall(ball, this);
		physics.manageBallMovement(ball, this, (int) canvas.getWidth(), (int) canvas.getHeight());
		Platform.runLater(this::doRestoreToInitialState);
	}

	private void doRestoreToInitialState() {
		fire.setDisable(false);
		ball.stopAndMoveTo(xOfCatapult, yOfCatapult);
		redraw();
	}

	@FXML
	private void aboutItemAction(ActionEvent ev) {
		Alert a = new Alert(Alert.AlertType.INFORMATION, "END0013", ButtonType.OK);
		a.setTitle("Author");
		a.show();
	}

	
	private void init() {
		xOfCatapult = Constants.INDENTATION;
		yOfCatapult = (int) (canvas.getHeight() - Constants.INDENTATION);
		catapult = new Catapult(xOfCatapult, yOfCatapult, Constants.LEN_OF_CATAPULT);

		power.setValue(Constants.INITIAL_POWER);
		power.setMin(Constants.MIN_POWER);
		power.setMax(Constants.MAX_POWER);
		power.valueProperty().addListener(this::powerChanged);

		catapult.setPower((int) power.getValue());
		
		angle.valueProperty().addListener(this::angleChanged);
		catapult.setAngle((int) angle.getValue());
		len.valueProperty().addListener(this::lenChanged);
		catapult.setLen((int) len.getValue());

		objectManager = new ObjectManager();

		objectManager.add(new WoodBrick(100, 200));
                objectManager.add(new IronBrick(200, 250));
                objectManager.add(new AlienShip(300, 220));
                

		ball = new Ball(xOfCatapult, yOfCatapult, Constants.SIZE_OF_BALL);
		fire.setOnAction(this::firePressed);
		physics = new Physics(Constants.GRAVITY);
		redraw();
	}

	private void redraw() {
		GraphicsContext gc = canvas.getGraphicsContext2D();
		redrawCanvas(gc);
		catapult.paint(gc);
		ball.paint(gc);
                
		objectManager.redraw(ball, gc);
	}

	private void redrawCanvas(GraphicsContext gc) {
		Paint original = gc.getFill();
		gc.setFill(Color.LIGHTYELLOW);
		gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
		gc.setFill(original);
	}
}
