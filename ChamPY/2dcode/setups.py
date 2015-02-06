

def setup_source_class(SOURCE_TYPE):
    
    if SOURCE_TYPE == "circle":
        import sourcetypes.circle as SOURCE_CLASS
        FLAG = False
    elif SOURCE_TYPE == "ellipse":
        import sourcetypes.ellipse as SOURCE_CLASS 
        FLAG = False
    elif SOURCE_TYPE == "rectangle":
        import sourcetypes.ellipse as SOURCE_CLASS   
        FLAG = False    
    elif SOURCE_TYPE == "cyl_plate":
        import sourcetypes.cyl_plate as SOURCE_CLASS    
        FLAG = False    
    else:
        FLAG = True
        
    return (FLAG, SOURCE_CLASS)    