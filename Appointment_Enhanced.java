package appointments;
// Imports necessary Java utility classes for handling dates and calendar calculations
import java.util.Calendar;
import java.util.Date;

public class Appointment { 
	
	//required variables
	private String aptID;
	private Date aptDate;
	private String aptDescription;
	
	//constructor
	public Appointment(String aptID, Date aptDate
			, String aptDescription) {

		// Creating variable for maximum allowed date (current date + 1 year)
        Calendar cal = Calendar.getInstance();
        cal.setTime(new Date());
        cal.add(Calendar.YEAR, 1);
        Date maxDate = cal.getTime();
		
		//Throws an exception if aptID is empty or less than 10 characters
		if (aptID == null || aptID.length() > 10) {
			throw new IllegalArgumentException("Invalid appointment ID input.");
		}
		//Throwas exception if aptDate is empty, before current date, or after a year ahead.
		if (aptDate == null || aptDate.before(new Date()) || aptDate.after(maxDate)) {
			throw new IllegalArgumentException("Invalid appointment date input.");
		}
		//Throws an exception if aptDescription is empty or more than 50 characters
		if (aptDescription == null || aptDescription.length() > 50) {
			throw new IllegalArgumentException("Invalid appointment description input.");
		}
		
		//Assign parameters to objects variables
		this.aptID = aptID;
		this.aptDate = aptDate;
		this.aptDescription = aptDescription;
	}

	//gets the aptDate
	public Date getAptDate() {
		return aptDate;
	}
	//updates the aptDate
	public void setAptDate(Date aptDate) {
		this.aptDate = aptDate;
	}
	//gets the aptDescription
	public String getAptDescription() {
		return aptDescription;
	} 
	//updates the aptDescription
	public void setAptDescription(String aptDescription) {
		this.aptDescription = aptDescription;
	}
	//gets the aptID
	public String getAptID() {
		return aptID;
	}
}
