function cleanup --description 'Clean files after specified days of inactivity' --argument target_directory days_inactive recursive dry_run excluded_files_dirs sort_type confirmation

    #Set variable containing files to be deleted
    set -l filtodel

    #Set variable containing arguments for sort
    set -l sortargs
    
    #Set variable containing arguments for find
    set -l findargs

    #Set sorting ascending or descending
    if test "$sort_type" = desc
        set sortargs -hr
    else if test "$sort_type" = asc
        set sortargs -h
    else
        echo "Error is choosing sorting order! It can either be asc or desc."
        return
    end

    #Set recursive in findargs
    if ! $recursive
        set -a findargs -maxdepth 1
    end
    
    #Remove excluded files from filtodel
 
    echo "Excluding files with name:"
    if string match -q "* *" $excluded_files_dirs 
	set -l excluded_files_names (string split ' ' $excluded_files_dirs)
    else
	set -l excluded_files_names $excluded_files_dirs
    end
    set -l excluded_files_names (string split ' ' $excluded_files_dirs)
    for i in $excluded_files_names
	echo $i
	set -a findargs ! -name $i 
    end
 

    #Set file directories to be deleted in filtodel
    set -a filtodel (find "$target_directory" $findargs -type f -atime +$days_inactive -exec du -ah {} + | sort "$sortargs" | cut -f2)
    
    #Print paths of files and directories to be deleted
    echo "Paths of files to be deleted:"
    for i in $filtodel
	echo $i
    end


    #If Dry Run mode,notify the user
    if $dry_run
        echo "Dry run mode enabled! No files will be affected."
    end

    #If comfirmation is set,notify the user
    if $confirmation
	echo "Confirmation enabled! You will be asked before removing each file."
    end



    #Remove files
    #  Check if confirmation is set, then check if
    #  dry run is set and remove accordingly.
    
    for fil in $filtodel
	    #check confirmation
            if $confirmation
		#ask then delete
		read -l -P "Are you sure you want to delete $fil ? [y/N] " confirm
		switch $confirm
		case Y y
			#if dryrun do nothing
			if ! $dry_run
				rm $fil
				echo "Deleted $fil "
			else
				echo "Would delete $fil but Dry Run is enabled!"
			end
		case '' N n
			echo "Skipping $fil "
		end
	    else
		#delete without asking
		#if dryrun do nothing
		if ! $dry_run
			rm $fil
			echo "Deleted $fil "
		else
			echo "Would delete $fil but Dry Run is enabled!"
		end
	    end
     end
    
    #Find and delete empty folders in target directory
    find $target_directory -type d -empty -exec rm -d {} +

end
